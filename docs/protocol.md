# Arduino SD Card Serial Protocol

This protocol enables efficient, chunked file transfers and file management between a client and an Arduino device with
an SD card, using a serial connection. All file data is Base64-encoded.

## Notes

- File data chunks are Base64-encoded.
- **Default chunk size:** 64 bytes (decoded).
- The client must wait for acknowledgments before proceeding.
- Protocol is newline-terminated and case-insensitive for commands.

All commands should be sent from the client after Arduino writes "Ready" when it is ready to receive commands after SD
card initialization.

---

## Command Summary

| Command        | Direction        | Description                           | Arguments                      | Response                                                    | Details                      |
|----------------|------------------|---------------------------------------|--------------------------------|-------------------------------------------------------------|------------------------------|
| `LIST`         | Client → Arduino | List all files and folders on SD card | None                           | Multiple: `ENTRY <path> <type> <size>`, then `OK END`       | [See details](#list)         |
| `LISTFOLDER`   | Client → Arduino | List contents of a specific folder    | `<folderpath>`                 | Multiple: `ENTRY <path> <type> <size>`, then `OK END`       | [See details](#listfolder)   |
| `READFILE`     | Client → Arduino | Read a file in chunks                 | `<filepath>`                   | `OK START SIZE=<size>`, then `DATA <base64>`, then `OK END` | [See details](#readfile)     |
| `WRITEFILE`    | Client → Arduino | Begin uploading a file in chunks      | `<filepath> SIZE=<total_size>` | `OK READY`                                                  | [See details](#writefile)    |
| `SETCONFIG`    | Client → Arduino | Set configuration options             | `[CHUNKSIZE=<size>]`           | `OK CONFIG SET <key>=<value>`                               | [See details](#setconfig)    |
| `GETCONFIG`    | Client → Arduino | Get current configuration             | None                           | `CONFIG <key>=<value> ...`, then `OK END`                   | [See details](#getconfig)    |
| `DATA`         | Both             | Transfer a chunk of file data         | `<base64chunk>`                | `OK RECEIVED` (write), no reply (read)                      | [See details](#data)         |
| `END`          | Client → Arduino | End of file upload                    | None                           | `OK STORED`                                                 | [See details](#end)          |
| `DELETEFILE`   | Client → Arduino | Delete a file                         | `<filepath>`                   | `OK DELETED`                                                | [See details](#deletefile)   |
| `DELETEFOLDER` | Client → Arduino | Delete a folder and its contents      | `<folderpath>`                 | `OK DELETED`                                                | [See details](#deletefolder) |
| `OK`           | Arduino → Client | Success acknowledgment                | Optional message               | None                                                        | [See details](#ok-and-err)   |
| `ERR`          | Arduino → Client | Error message                         | Error description              | None                                                        | [See details](#ok-and-err)   |

---

## <a name="list"></a>LIST

**Description:**  
Lists all files and folders on the SD card recursively.

**Usage:**  
Client → Arduino:  
`LIST`

**Response:**

- Multiple: `ENTRY <path> <type> <size>`
    - `<type>` is `FILE` or `FOLDER`
    - `<size>` is file size in bytes, or `0` for folders
- `OK END`

**Errors:**

- `ERR SDInitFailed`

---

## <a name="listfolder"></a>LISTFOLDER

**Description:**  
Lists the contents of a specific folder.

**Usage:**  
Client → Arduino:  
`LISTFOLDER /path/to/folder`

**Response:**

- Multiple: `ENTRY <path> <type> <size>`
- `OK END`

**Errors:**

- `ERR MissingPath`
- `ERR FolderNotFound`
- `ERR SDInitFailed`

---

## <a name="readfile"></a>READFILE

**Description:**  
Requests the Arduino to send the contents of a file in Base64-encoded chunks.

**Usage:**  
Client → Arduino:  
`READFILE /path/to/file`

**Response:**

- `OK START SIZE=<file_size>`
- Multiple: `DATA <base64_chunk>`
- `OK END`

**Errors:**

- `ERR MissingPath`
- `ERR FileNotFound`
- `ERR SDInitFailed`

---

## <a name="writefile"></a>WRITEFILE

**Description:**  
Initiates a chunked upload of a file to the Arduino SD card.

**Usage:**  
Client → Arduino:  
`WRITEFILE /path/to/file SIZE=<total_size>`

**Response:**

- `OK READY`

**Followed by:**

- Multiple: `DATA <base64_chunk>` (Client → Arduino)
- After each: `OK RECEIVED` (Arduino → Client)

**End upload:**  
Client → Arduino:  
`END`  
Arduino → Client:  
`OK STORED`

**Errors:**

- `ERR MissingArguments`
- `ERR MissingSize`
- `ERR FileOpenFailed`
- `ERR NotInWriteMode`

---

## <a name="setconfig"></a>SETCONFIG

**Description:**  
Sets configuration options. Currently, only `CHUNKSIZE` is supported.

- `CHUNKSIZE`: Size of file transfer chunks in bytes (default: 64).

**Usage:**  
Client → Arduino:  
`SETCONFIG CHUNKSIZE=<size>`

**Response:**  
Arduino → Client:  
`OK CONFIG SET CHUNKSIZE=<size>`

**Errors:**

- `ERR InvalidConfigKey`
- `ERR InvalidConfigValue`
- `ERR SDInitFailed`

---

## <a name="getconfig"></a>GETCONFIG

**Description:**  
Returns the current configuration values.

**Usage:**  
Client → Arduino:  
`GETCONFIG`

**Response:**

- `CONFIG CHUNKSIZE=<size>`
- `OK END`

**Errors:**

- `ERR SDInitFailed`

---

## <a name="data"></a>DATA

**Description:**  
Transfers a chunk of file data encoded in Base64.

- **Reading:**  
  Arduino → Client:  
  `DATA <base64_chunk>`  
  (No response expected)

- **Writing:**  
  Client → Arduino:  
  `DATA <base64_chunk>`  
  Arduino → Client:  
  `OK RECEIVED`

**Errors:**

- `ERR NotInWriteMode`

---

## <a name="end"></a>END

**Description:**  
Signals the end of a chunked write upload.

**Usage:**  
Client → Arduino:  
`END`

**Response:**  
Arduino → Client:  
`OK STORED`

**Errors:**

- `ERR NotInWriteMode`

---

## <a name="deletefile"></a>DELETEFILE

**Description:**  
Deletes a file from the SD card.

**Usage:**  
Client → Arduino:  
`DELETEFILE /path/to/file`

**Response:**  
Arduino → Client:  
`OK DELETED`

**Errors:**

- `ERR MissingPath`
- `ERR FileNotFound`
- `ERR DeleteFailed`
- `ERR SDInitFailed`

---

## <a name="deletefolder"></a>DELETEFOLDER

**Description:**  
Deletes a folder and all its contents from the SD card.

**Usage:**  
Client → Arduino:  
`DELETEFOLDER /path/to/folder`

**Response:**  
Arduino → Client:  
`OK DELETED`

**Errors:**

- `ERR MissingPath`
- `ERR FolderNotFound`
- `ERR DeleteFailed`
- `ERR SDInitFailed`

---

## <a name="ok-and-err"></a>OK and ERR Responses

- `OK` responses acknowledge successful command or data receipt, optionally with additional info (e.g.,
  `OK START SIZE=...`).
- `ERR` responses indicate errors and include an error message.

**Common Error Messages:**

| Error Message            | Meaning                                       |
|--------------------------|-----------------------------------------------|
| `ERR FileNotFound`       | File does not exist or cannot be opened       |
| `ERR FolderNotFound`     | Folder does not exist                         |
| `ERR MissingPath`        | Required file or folder path argument missing |
| `ERR MissingSize`        | Required size argument missing                |
| `ERR FileOpenFailed`     | Failed to open file for writing               |
| `ERR NotInWriteMode`     | `DATA` or `END` sent outside a write session  |
| `ERR SDInitFailed`       | Failed to initialize SD card                  |
| `ERR UnknownCommand`     | Unknown or unsupported command                |
| `ERR DeleteFailed`       | Failed to delete file or folder               |
| `ERR InvalidConfigKey`   | Provided config key is invalid                |
| `ERR InvalidConfigValue` | Provided config value is invalid              |

---
