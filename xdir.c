/*******************************************************************************
 * xdir by Geoffrey Sessums
 * Purpose:
 *   This program uses low level I/O functions to create an xdir command in C.
 * Command Parameters:
 *   xdir directory switches
 * Input:
 *   Directory
 *   -l (switch)
 *   -a (switch)
 * Results:
 *   xdir directory: Prints the directory name followed by a colon, then prints
 *     any files that DO NOT begin with "."
 *     Example:
 *     Data :
 *         file5
 *         file6
 *         Program4
 *         Program5
 *         Program2
 *         Program3
 *         file4
 *   Option -l: prints the directory name follwed by a colon, then prints any 
 *     files that DO NOT begin with "." followed by the file type, number of
 *     512 byte blocks, and size in bytes.
 *     Example:
 *       Data :
 *           file5 F 8 blks 167 bytes
 *           file6 F 8 blks 121 bytes
 *           Program4 D 8 blks 4096 bytes
 *           Program5 D 8 blks 4096 bytes
 *           Program2 D 8 blks 4096 bytes
 *           Program3 D 8 blks 4096 bytes
 *           file4 F 8 blks 87 bytes
 *           
 *   Option -a: prints the directory name followed by a colon, then prints the
 *     file names within the directory.
 *     Example:
 *       Data :
 *           . D 8 blks 4096 bytes
 *           .. D 8 blks 4096 bytes
 *           file5 F 8 blks 167 bytes
 *           file6 F 8 blks 121 bytes
 *           .mydot F 8 blks 25 bytes
 *           Program4 D 8 blks 4096 bytes
 *           Program5 D 8 blks 4096 bytes
 *           Program2 D 8 blks 4096 bytes
 *           Program3 D 8 blks 4096 bytes
 *           file4 F 8 blks 87 bytes
 *
 *   Option -l -a: prints the directory name followed by a colon, then prints
 *     the file names within the directory followed by file type, number of 512
 *     byte blocks, and size in bytes.
 * Returns:
 *   0 normal
 * Notes:
 *   none
 * ****************************************************************************/

// Included files
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

// Prototypes
void errExit(const char szFmt[], ...);

// Main Program
int main(int argc, char *argv[])
{
  DIR *pDir;
  char szFullFileNm[500];
  char cFileType;
  struct dirent *pDirent;
  struct stat statBuf;
  int irc;

  if (argc < 2) {
    errExit("too few arguments, directory name needed");
  }

  // Open directory
  pDir = opendir(argv[1]);

  // Check if directory can be opened
  if (pDir == NULL) {
    errExit("opendir could not open '%s': %s", argv[1], strerror(errno));
  }

  // Process no switches
  if (argc == 2) {
    // Print the directory name
    printf("%s :\n", argv[1]);
    // Print directory contents that DO NOT begin with "."
    while ((pDirent = readdir(pDir)) != NULL) {
      if (pDirent->d_name[0] != '.') {
        printf("    %s\n", pDirent->d_name);
      }
    }
    closedir(pDir);
    return 0;
  } else if (argc == 3) {
    if (argv[2][0] != '-') {
      printf("error: missing switch '-'\n"); 
      return 0;
    }
    // Option a: Print the directory name and contents
    if (argv[2][1] == 'a') {
        // Print the directory name
        printf("%s :\n", argv[1]);
        // Print the contents of the directory
        while ((pDirent = readdir(pDir)) != NULL) {
            printf("    %s\n", pDirent->d_name);
        }
        closedir(pDir);
        return 0;
    // Option l: Print the directory, files that DO NOT begin with ".",
    // file name, type, number of blocks, and size
    } else if (argv[2][1] == 'l') {
      // Print the directory name
      printf("%s :\n", argv[1]);
      // Print directory contents that DO NOT begin with "."
      while ((pDirent = readdir(pDir)) != NULL) {
        if (pDirent->d_name[0] != '.') {
          snprintf(szFullFileNm, 500, "%s/%s", argv[1], pDirent->d_name);
          irc = stat(szFullFileNm, &statBuf);
          if (S_ISDIR(statBuf.st_mode)) {
              cFileType = 'D';
          } else if (S_ISFIFO(statBuf.st_mode)) {
              cFileType = 'P';
          } else if (S_ISREG(statBuf.st_mode)) {
              cFileType = 'F';
          } else if (S_ISLNK(statBuf.st_mode)) {
              cFileType = 'L';
          } else {
              cFileType = 'L';
          }
          printf("    %s %c %lld blks %lld bytes\n", pDirent->d_name
              , cFileType
              , statBuf.st_blocks
              , statBuf.st_size);
        }
      }
      closedir(pDir);
    } else {
        printf("option '%c' does not exist\n", argv[2][1]);
    }
  } else if (argc == 4) {
    if (argv[3][0] != '-' || argv[2][0] != '-') {
      printf("error: missing switch '-'\n");
      return 0; 
    }
    if ((argv[3][1] == 'a' || argv[3][1] == 'l')
        && (argv[2][1] == 'a' || argv[2][1] == 'l')) {
      // Print the directory name
      printf("%s :\n", argv[1]);
      // Print directory contents that DO NOT begin with "."
      while ((pDirent = readdir(pDir)) != NULL) {
        snprintf(szFullFileNm, 500, "%s/%s", argv[1], pDirent->d_name);
        irc = stat(szFullFileNm, &statBuf);
        if (S_ISDIR(statBuf.st_mode)) {
          cFileType = 'D';
        } else if (S_ISFIFO(statBuf.st_mode)) {
          cFileType = 'P';
        } else if (S_ISREG(statBuf.st_mode)) {
          cFileType = 'F';
        } else if (S_ISLNK(statBuf.st_mode)) {
          cFileType = 'L';
        } else {
          cFileType = 'L';
        }
          printf("    %s %c %lld blks %lld bytes\n", pDirent->d_name
              , cFileType
              , statBuf.st_blocks
              , statBuf.st_size);
      }
      closedir(pDir);
    } else {
      printf("one of the option you selected does not exist\n");
    }
  }
  return 0;
}
