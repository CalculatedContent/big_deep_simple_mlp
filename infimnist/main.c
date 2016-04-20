/* ======================================================
 * The Infinite MNIST dataset
 *
 * The files named "data/t10k-*" and "data/train-*" are the original MNIST
 * files (http://yann.lecun.com/exdb/mnist/).  The other files were initially
 * written for the experiments reported in paper "Training Invariant Support
 * Vector Machines using Selective Sampling" by Loosli, Canu, and Bottou
 * (http://leon.bottou.org/papers/loosli-canu-bottou-2006)
 *
 * Copyright (C) 2006- Leon Bottou and Gaelle Loosli                            
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details. You should have received a copy of the GNU General Public
 * License along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111, USA
 *
 * ====================================================== */


#include "infimnist.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#if defined(_WIN32)
# include <io.h>
# include <fcntl.h>
#endif

static void usage(void)
{
  fprintf(stderr,
          "Usage: infimnist [-d <dir>] <format> <firstindex> [<lastindex>]\n"
          " Format should be a nonambiguous prefix of:\n"
          " patterns, labels, svmlight, vw, arff, display\n");
  exit(10);
}

static void write32(int x)
{
  char buf[4];
  buf[0] = (x>>24)&0xff;
  buf[1] = (x>>16)&0xff;
  buf[2] = (x>>8)&0xff;
  buf[3] = (x>>0)&0xff;
  fwrite(buf,4,1,stdout);
} 

const char *datadir = "data";
char format = 0;
long firstindex = 10000;
long lastindex = 69999;

int main(int argc, char **argv)
{
  infimnist_t *p;
  char *s;
  int l;
  long i;
  /* parse */
  if (argc > 4 && !strcmp(argv[1],"-d"))
    {
      datadir = argv[2];
      argc -= 2;
      argv += 2;
    }
  if (argc < 3 || argc > 4)
    usage();
  l = strlen(argv[1]);
  if (! strncmp(argv[1],"patterns",l) ||
      ! strncmp(argv[1],"labels",l) ||
      ! strncmp(argv[1],"svmlight",l) ||
      ! strncmp(argv[1],"vw",l) ||
      ! strncmp(argv[1],"arff",l) ||
      ! strncmp(argv[1],"display",l) )
    format = argv[1][0];
  else
    usage();
  firstindex = strtol(argv[2],&s,10);
  if (*s || firstindex<0) 
    usage();
  lastindex = firstindex;
  if (argc > 3)
    lastindex = strtol(argv[3],&s,10);
  if (*s || lastindex<firstindex)
    usage();
  /* output mnist style binary files */
  if (format == 'p' || format == 'l')
    {
#if defined(__CYGWIN32__)
      setmode(fileno(stdout), O_BINARY);
#elif defined(_WIN32) 
      _setmode(_fileno(stdout), _O_BINARY);
#endif
    }
  /* create */
  p = infimnist_create(datadir);
  /* header */
  if (format == 'p') 
    {
      write32(0x803);
      write32(lastindex-firstindex+1);
      write32(28);
      write32(28);
    } 
  else if (format == 'l') 
    {
      write32(0x801);
      write32(lastindex-firstindex+1);
    }
  else if (format == 'a')
    {
      printf("@relation mnist_%ld_%ld\n", firstindex, lastindex);
      for (l=0; l<784; l++) 
        printf("@attribute a_%d numeric\n", l);
      printf("@attribute digit {0,1,2,3,4,5,6,7,8,9}\n@data\n");
    }
  /* data */
  for (i=firstindex; i<=lastindex; i++)
    {
      if (format == 'd')
        {
          char b = infimnist_get_label(p, i);
          const unsigned char *s = infimnist_get_pattern(p, i);
	  const char map[16] = "  ....:::::###@@";
	  int r;
	  printf("===== %ld:%d =====\n", i, b);
          for (l=r=0; l<784; l++)
	    {
	       if (r == 0) 
	         printf("\t");
	       printf("%c", map[s[l]>>4]);
	       if (++r == 28)
	         { r = 0; printf("\n"); }
	    }
        }
      else if (format == 'l')
        {
          char b = infimnist_get_label(p, i);
          fwrite(&b,1,1,stdout);
        }
      else if (format == 'p')
        {
          const unsigned char *s = infimnist_get_pattern(p, i);
          fwrite(s,784,1,stdout);
        }
      else if (format == 's' || format == 'v')
        {
          char b = infimnist_get_label(p, i);
          const unsigned char *s = infimnist_get_pattern(p, i);
          printf("%d", b);
          if (format == 'v')
            printf(" |");
          for (l=0; l<784; l++)
            if (s[l] > 0) 
              printf(" %d:%d", l+1, s[l]);
          printf("\n");
        }
      else if (format == 'a')
        {
          char b = infimnist_get_label(p, i);
          const unsigned char *s = infimnist_get_pattern(p, i);
          printf("{");
          for (l=0; l<784; l++)
            if (s[l] > 0) 
              printf("%d %d,", l, s[l]);
          printf("784 %d}\n", b);
	}
    }
  /* terminate */
  fflush(stdout);
  infimnist_destroy(p);
  return 0;
}


