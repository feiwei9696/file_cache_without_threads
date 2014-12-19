#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAXSIZE  50      // Maximum length for file name.
#define MAXENTRIES 100   // Maximum no of entries cache can hold
#ifdef DEBUG           // To enable debug mode compile with -DDEBUG=1
#define DEBUG 1
#endif
//
// Copyright (c) 2013 Nutanix Inc. All rights rneserved.
//
// The problem is to implement a file cache in C that implements the defined
// interface given below for struct 'file_cache'. The typical usage is for a
// client to call 'file_cache_pin_files()' to pin a bunch of files in the cache
// and then either read or write to their in-memory contents in the cache.
// Writing to a cache entry makes that entry 'dirty'. Before a dirty entry can
// be evicted from the cache, it must be unpinned and has to be cleaned by
// writing the corresponding data to storage.
//
// All files are assumed to have size 10KB. If a file doesn't exist to begin
// with, it should be created and filled with zeros - the size should be 10KB.
//
// 'file_cache' should be a thread-safe object that can be simultaneously
// accessed by multiple threads. If you are not comfortable with concurrent
// programming, then it may be single-threaded (see alternative in the
// file_cache_pin_files() comment). To implement the problem in its entirety
// may require use of third party libraries and headers. For the sake of
// convenience, it is permissible (although not preferred) to substitute
// external functions with stub implementations, but in doing so, please be
// clear what the intended behavior and side effects would be.
//
// Do not be overly concerned about portability. Pick your platform of choice
// (Nutanix develops on Linux) and be consistent.
//
// The problem has an upper limit of two hours. Note that we'd rather see a
// stable and clean solution that implements a subset of the functionality than
// a complete but-buggy one.
//
// If you have any questions, please email both brian@nutanix.com and
// bnc@nutanix.com. If no reply is received in a timely manner, please make a
// judgement call and state your assumptions in the code or response email.

#ifndef _NUTANIX_FILE_CACHE_H_
#define _NUTANIX_FILE_CACHE_H_

typedef struct file_cache file_cache;

/* Definition of file_cache structure. Each file has a file_cahe object associated with it */
struct file_cache {
   char filename[MAXSIZE]; // Name of the file
   int pin;                // {0,1} Pin value of 1 indicates file is in cache, 0 not in cache.
   int dirty;              // {0,1} Dirty bit. 1 indicates that buf contents are not written to local file system. 0 indicates cache and local filesystem are consistent.
   char *buf;              // buffer to hold the data already read or data to be written to file system.
   file_cache* next;       // pointer to the next element in the cache list. For tail node(last node in cache list) next is NULL.
   file_cache* prev;       // pointer to the prev element in the cache list. For head node (first node in cache list)) presv is NULL.
};

void file_cache_destroy(file_cache* );
file_cache* search_cache(file_cache* ,char*);
file_cache* add_to_cache(char*);
void file_cache_pin_files(file_cache*,const char**,int);
void write_to_file(file_cache*);
void file_cache_unpin_files(file_cache* ,const char**,int);
const char *file_cache_file_data(file_cache*, const char*);
char *file_cache_mutable_file_data(file_cache*, const char*);


#endif  // _NUTANIX_FILE_CACHE_H_
