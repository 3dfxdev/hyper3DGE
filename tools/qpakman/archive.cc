//------------------------------------------------------------------------
//  Archiving files to/from a PAK
//------------------------------------------------------------------------
// 
//  Copyright (c) 2008  Andrew J Apted
// 
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//------------------------------------------------------------------------

#include "headers.h"

#include <errno.h>

#include <map>
#include <algorithm>

#include "archive.h"
#include "pakfile.h"
#include "q1_structs.h"

extern std::vector<std::string> input_names;

extern bool opt_recursive;
extern bool opt_overwrite;


std::map<std::string, int> all_created_dirs;
std::map<std::string, int> all_pak_lumps;

#define ARC_MAX_DEPTH  5


const char *SanitizeOutputName(const char *name)
{
  // Sanitize the output filename as follows:
  //
  // (a) replace spaces and weird chars with '_' (show WARNING)
  // (b) replace \ with /
  // (c) strip leading / characters
  // (d) disallow .. and //

  while (*name == '/' || *name == '\\' || *name == '.')
    name++;

  int name_len = strlen(name);

  char *filename = StringNew(name_len + 32);
  char *pos = filename;

  bool warned = false;

  for (; *name; name++)
  {
    char ch = *name;

    if (ch == ' ')  ch = '_';
    if (ch == '\\') ch = '/';

    if ((ch == '.' && name[1] == '.') ||
        (ch == '/' && name[1] == '/'))
    {
      continue;
    }

    if (! (isalnum(ch) || ch == '_' || ch == '-' ||
           ch == '/'   || ch == '.'))
    {
      if (! warned)
      {
        printf("WARNING: removing weird characters from name (\\%03o)\n",
               (unsigned char)ch);
        warned = true;
      }

      ch = '_';
    }

    *pos++ = ch;
  }

  *pos = 0;

  if (strlen(filename) == 0)
  {
    printf("FAILURE: illegal filename\n");
    return NULL;
  }
  
  return filename;
}


static bool ARC_CreateNeededDirs(const char *filename)
{
  for (int level = 0; level < 60; level++)
  {
    const char *end_p = filename;

    for (int i = 0; i <= level; i++)
    {
      end_p = strchr(end_p, '/');

      if (! end_p)
        return true;

      if (i < level)
        end_p++;
    }

    char *dir_name = StringNew(end_p - filename + 4);

    StringMaxCopy(dir_name, filename, end_p - filename);

    // check whether we made the directory before
    if (all_created_dirs.find(dir_name) == all_created_dirs.end())
    {
      // add it to created-list anyway, to prevent future warnings
      all_created_dirs[dir_name] = 1;

      if (! FileMakeDir(dir_name))
      {
        printf("WARNING: could not create directory: %s\n", dir_name);
#if 0
        StringFree(dir_name);
        return false;
#endif
      }
    }

    StringFree(dir_name);
  }

  // should never get here (but no biggie if we do)
  return false;
}


bool ARC_ExtractOneFile(int entry, const char *name)
{
  const char * filename = SanitizeOutputName(name);
  if (! filename)
    return false;


  if (FileExists(filename) && ! opt_overwrite)
  {
    printf("FAILURE: will not overwrite file: %s\n\n", filename);

    StringFree(filename);
    return false;
  }

  if (! ARC_CreateNeededDirs(filename))
  {
#if 0
    // error message displayed by ARC_CreateNeededDirs()
    StringFree(filename);
    return false;
#endif
  }


  int entry_len = PAK_EntryLen(entry);

  bool failed = false;

  FILE *fp = fopen(filename, "wb");
  if (fp)
  {
    static byte buffer[2048];

    // transfer data from PAK into new file
    int position = 0;

    while (position < entry_len)
    {
      int count = MIN((int)sizeof(buffer), entry_len - position);

      if (! PAK_ReadData(entry, position, count, buffer))
      {
        printf("FAILURE: read error on %d bytes\n\n", count);
        failed = true;
        break;
      }

      if (1 != fwrite(buffer, count, 1, fp))
      {
        printf("FAILURE: write error on %d bytes\n\n", count);
        failed = true;
        break;
      }

      position += count;
    }

    fclose(fp);
  }
  else
  {
    printf("FAILURE: cannot create output file: %s\n\n", filename);
    failed = true;
  }

  StringFree(filename);

  return ! failed;
}


void ARC_ExtractPAK(const char *filename)
{
  if (! PAK_OpenRead(filename))
    FatalError("Cannot open PAK file: %s\n", filename);

  printf("\n");
  printf("--------------------------------------------------\n");

  int num_files = PAK_NumEntries();

  int skipped  = 0;
  int failures = 0;

  for (int i = 0; i < num_files; i++)
  {
    const char *name = PAK_EntryName(i);

    printf("Unpacking entry %d/%d : %s\n", i+1, num_files, name);

    if (! ARC_ExtractOneFile(i, name))
      failures++;
  }

  printf("--------------------------------------------------\n");
  printf("\n");

  PAK_CloseRead();

// printf("Skipped %d entries\n", skipped);

  printf("Extracted %d entries, with %d failures\n",
         num_files - failures - skipped, failures);
}


//------------------------------------------------------------------------

// forward declaration
void ARC_StoreDir(int depth, const char *path,
                  int *num_pack, int *failures, int *skipped);


void Spaces(int depth)
{
  for (; depth > 0; depth--)
    printf("  ");
}


const char * MakePakLumpName(const char *prefix, const char *filename)
{
  //!!!! FIXME MakePakLumpName

  std::string full(prefix);

  full += filename;

  return StringDup(full.c_str());
}


void ARC_StoreFile(int depth, int list_index, int list_total,
                   const char *prefix, const char *path, bool is_dir,
                   int *num_pack, int *failures, int *skipped)
{
  if (is_dir)
  {
    if (! opt_recursive)
    {
      printf("SKIPPING DIRECTORY: %s\n", path);

      (*skipped) += 1;
      return;
    }

    if (depth+1 >= ARC_MAX_DEPTH)
    {
      Spaces(depth);
      printf("SKIPPING TOO-DEEP DIRECTORY: %s\n", path);

      (*skipped) += 1;
      return;
    }

    Spaces(depth);
    printf("Descending into directory: %s\n", path);

    ARC_StoreDir(depth + 1, path,
                 num_pack, failures, skipped);

    // we don't bump the 'num_pack' value here because the
    // directory itself does not exist in the PAK file as a
    // separate entry.
    return;
  }


  // path refers to a normal file, create a PAK entry for it
  // and then copy the data.

  Spaces(depth);
  if (list_total > 0)
    printf("Processing %d/%d: %s\n", list_index, list_total, path);
  else
    printf("Processing: %s\n", path);

  const char *lump_name = MakePakLumpName(prefix, path);
  if (! lump_name)
  {
    (*failures) += 1;
    return;
  }

  if (all_pak_lumps.find(lump_name) != all_pak_lumps.end())
  {
    Spaces(depth);
    printf("FAILURE: Lump already exists, will not duplicate\n\n");

    StringFree(lump_name);

    (*failures) += 1;
    return;
  }

  all_pak_lumps[lump_name] = 1;


  FILE *fp = fopen(path, "rb");
  if (! fp)
  {
    Spaces(depth);
    printf("FAILURE: no such file\n\n");

    StringFree(lump_name);

    (*failures) += 1;
    return;
  }

  PAK_NewLump(lump_name);

  StringFree(lump_name);

  (*num_pack) += 1;


  // transfer data
  bool read_error = false;

  static byte buffer[1024];

  for (;;)
  {
    int count = fread(buffer, 1, (size_t)sizeof(buffer), fp);

    if (count == 0)  // EOF
      break;

    if (count < 0)  // Error
    {
      int what_error = errno;

      Spaces(depth);
      printf("FAILURE: error reading file: %s\n\n",
             (what_error == 0) ? "Unknown error" : strerror(what_error));

      read_error = true;
      break;
    }

    PAK_AppendData(buffer, count);
  }

  PAK_FinishLump();

  fclose(fp);

  if (read_error)
    (*failures) += 1;
}


typedef struct
{
  int depth;

  const char *prefix;

  int *num_pack;
  int *failures;
  int *skipped;
}
pak_scan_info_t;


static void PakDirScanner(const char *name, int flags, void *priv_dat)
{
  pak_scan_info_t *scan_info = (pak_scan_info_t *) priv_dat;

  if (flags & SCAN_F_Hidden)
  {
    return;
  }

  if (StringCaseCmp(name, "qpakman")     == 0 ||
      StringCaseCmp(name, "qpakman.exe") == 0)
  {
    Spaces(scan_info->depth);
    printf("SKIPPING MYSELF: %s\n", name);

    (* scan_info->skipped) += 1;
    return;
  }


#if 0
  Spaces(scan_info->depth);
  printf("Sucking up file: %s\n", name);
  return;
#else
  ARC_StoreFile(scan_info->depth, 0, 0,
                scan_info->prefix, name,
                (flags & SCAN_F_IsDir) ? true : false,
                scan_info->num_pack, scan_info->failures,
                scan_info->skipped);
#endif
}


void ARC_StoreDir(int depth, const char *path,
                  int *num_pack, int *failures, int *skipped)
{
  pak_scan_info_t scan_info;

  scan_info.depth    = depth;
  scan_info.num_pack = num_pack;
  scan_info.failures = failures;
  scan_info.skipped  = skipped;

  int result = ScanDirectory(path, PakDirScanner, &scan_info);

  if (result < 0)
  {
    Spaces(depth - 1);

    if (result == SCAN_ERR_NoExist)
      printf("FAILURE: no such directory\n\n");
    else
      printf("FAILURE: error scanning directory\n\n");

    (*failures) += 1;
    return;
  }

  if (result == 0)
  {
    Spaces(depth);
    printf("(empty directory)\n");
  }

  printf("\n");
}


static void PakDirScanner2(const char *name, int flags, void *priv_dat)
{
  pak_scan_info_t *scan_info = (pak_scan_info_t *) priv_dat;

  if (flags & SCAN_F_Hidden)
  {
    return;
  }

  if (StringCaseCmp(name, "qpakman")     == 0 ||
      StringCaseCmp(name, "qpakman.exe") == 0)
  {
    printf("SKIPPING MYSELF: %s\n", name);

//    (* scan_info->skipped) += 1;
    return;
  }


  const char *prefix = scan_info->prefix;

  std::string full_name(prefix);

  full_name += DIR_SEP_STR;

  full_name += std::string(name);

//  printf("Scanning ---> '%s'\n", full_name.c_str());

  input_names.push_back(full_name);

#if 0
  Spaces(scan_info->depth);
  printf("Sucking up file: %s\n", name);
  return;

  ARC_StoreFile(scan_info->depth, 0, 0,
                scan_info->prefix, name,
                (flags & SCAN_F_IsDir) ? true : false,
                scan_info->num_pack, scan_info->failures,
                scan_info->skipped);
#endif
}


void ARC_ProcessPath(const char *path)
{
  // absolute filenames are not allowed
  if (path[0] == '/' || path[0] == '\\' ||
      (isalpha(path[0]) && path[1] == ':'))
  {
    printf("SKIPPING ABSOLUTE PATH: %s\n", path);
    return;
  }

  if (PathIsDirectory(path))
  {
    printf("\n");
    printf("Processing directory: %s\n", path);

    pak_scan_info_t scan_info;

    scan_info.prefix = path;

    int result = ScanDirectory(path, PakDirScanner2, &scan_info);

  }
  else
  {
//    ARC_StoreFile(path);
    printf("Storing: %s\n", path);
  }
}


void ARC_CreatePAK(const char *filename)
{
  if (input_names.size() == 0)
    FatalError("No input files were specified!\n");

  if (! PAK_OpenWrite(filename))
    FatalError("Cannot create PAK file: %s\n", filename);

  printf("\n");
  printf("--------------------------------------------------\n");

  int num_pack = 0;
  int failures = 0;
  int skipped  = 0;

  // ALGORITHM
  //
  // The basic approach is to treat the 'input_names' vector as a
  // stack, and we pop each path_name off the top to process it.
  //
  // When the path is a file, we copy it into the output PAK, but
  // for directories we scan it and push all the names in that
  // directory onto the stack.

  // reverse out stack, so we process entries in the same order as
  // given on the command line.
  std::reverse(input_names.begin(), input_names.end());

  while (! input_names.empty())
  {
    const char *path = StringDup(input_names.back().c_str());

    input_names.pop_back();

    ARC_ProcessPath(path);

    StringFree(path);

///    ARC_StoreFile(0, 1+(int)j, (int)input_names.size(),
///                  "", path, PathIsDirectory(path),
///                  &num_pack, &failures, &skipped);
  }

  printf("--------------------------------------------------\n");
  printf("\n");

  PAK_CloseWrite();

  if (skipped > 0)
    printf("Skipped %d directories\n", skipped);

  printf("Packed %d files, with %d failures\n", num_pack, failures);
}

//--- editor settings ---
// vi:ts=2:sw=2:expandtab
