/*
     This file is part of PlibC.
     (C) 2005 Nils Durner (and other contributing authors)

     This library is free software; you can redistribute it and/or
     modify it under the terms of the GNU Lesser General Public
     License as published by the Free Software Foundation; either
     version 2.1 of the License, or (at your option) any later version.
  
     This library is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     Lesser General Public License for more details.
  
     You should have received a copy of the GNU Lesser General Public
     License along with this library; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * @file src/intl.c
 * @brief bindtextdomain()
 */

#include "plibc_private.h"

char *_win_bindtextdomain(const char *domainname, const char *dirname)
{
#ifdef HAVE_LIBINTL
  char szDirname[_MAX_PATH + 1];
  int i;
  
  if ((i = plibc_conv_to_win_path(dirname, szDirname)) != ERROR_SUCCESS)
  {
    SetErrnoFromWinError(i);

    return NULL;
  }
  /* There is nothing we could do: libintl will internally call CRT with
   * szDirname, so we can't convert it to UTF-8, and can't convince
   * libintl to use wide-character functions either.
   * So only call BINDTEXTDOMAIN() with ASCII/CP*-encoded dirnames.
   */
  return bindtextdomain(domainname, szDirname);
#else
  errno = ENOSYS;
  return NULL;
#endif
}

/* end of intl.c */
