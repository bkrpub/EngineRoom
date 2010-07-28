/*
 *  $Id: er_util.c 760 2009-02-11 01:24:39Z bkr $
 */

#include "er_util.h"

void * UTIL_NO_INSTRUMENT
util_map_image(const char *file, size_t *lengthPtr)
{
  struct stat sb;
  int fd;
  void *image;
  
  if( NULL != lengthPtr ) 
    *lengthPtr = 0;

  if( NULL == file ) 
    utilReturnWithMessage(NULL, "can not map NULL file");

  if( 0 != stat(file, &sb) )
    utilReturnWithMessage(NULL, "can not stat %s (%s)", file, strerror(errno));

  if( 0 > ( fd = open(file, O_RDONLY) ) )
    utilReturnWithMessage(NULL, "can not open %s (%s)", file, strerror(errno));

  image = mmap(NULL, (size_t) sb.st_size, PROT_READ, MAP_PRIVATE, fd, (off_t) 0);
  close(fd);

  if( (void *) -1 == image )
    utilReturnWithMessage(NULL, "can not mmap %s (%s)", file, strerror(errno));

  if( NULL != lengthPtr )
    *lengthPtr = (size_t) sb.st_size;

  return image;
}

void UTIL_NO_INSTRUMENT
util_unmap_image(void *image, size_t length)
{
  munmap(image, length);  
}


int util_asprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  int n = util_vasprintf(ret, fmt, ap);
  va_end(ap);
  return n;
}

int util_vasprintf(char **ret, const char *fmt, va_list ap)
{
	char dummy;
	char *buf = &dummy;
	va_list ap_copy;
	
	if( ret == NULL ) {
		return -1;
	}
	
	va_copy(ap_copy, ap);
	
	int len = vsnprintf(buf, 1, (fmt), ap_copy); /* 1, not 0 for Solaris, man vsnprintf -> NOTES */
	
	if( len < 0 ) {
		*ret = NULL;
		return -1;
	}
	
	buf = malloc((size_t) len + 1);
	
	if( NULL == buf ) {
		*ret = NULL;
		return -1;
	}
	
	len = vsnprintf(buf, (size_t)len+1, (fmt), ap);
	
	*ret = buf;
	return len;
}

int util_log_asprintf(char **result, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);

  int ret = util_log_vasprintf(result, fmt, args);

  va_end(args);

  return ret;
}

int util_log_vasprintf(char **result, const char *fmt, va_list args)
{
    int ret;

    struct timeval tv;
    struct timezone tz;
    struct tm tm_gmt;

    if( result ) 
      *result = NULL;

    gettimeofday(&tv, &tz);

    time_t tt = tv.tv_sec;
    gmtime_r(&tt, &tm_gmt);

    char timestamp[ sizeof("YYYY-MM-DD HH:MM:SS") ];

    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &tm_gmt);

    char *msg = NULL;

    if( NULL != fmt )
      util_vasprintf(&msg, fmt, args);

#if 1
    ret = util_asprintf(result, "%10llu.%06d %s %llu %s", 
	    (unsigned long long)tv.tv_sec, (int) tv.tv_usec, timestamp, (unsigned long long) getpid(), 
	    msg ? msg : "");
#else
    int minutes = tm_gmt.tm_hour * 60 + tm_gmt.tm_min - tz.tz_minuteswest;
    
    if( minutes < 0 )
      minutes = 24 * 60 - ( -minutes % ( 24 * 60 ) );

    if( minutes >= 24*60 )
      minutes %= ( 24 * 60 );

    ret = util_asprintf(result, "%s.%06dZ %02d:%02d %llu %s", 
	    timestamp, (int)tv.tv_usec, minutes / 60, minutes % 60,
	    (unsigned long long) getpid(), 
	    msg ? msg : "");
#endif

    free(msg);

    return ret;
}


