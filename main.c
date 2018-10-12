#include "ivrHttp.h"
#include <string.h>
#include <stdio.h>
#include "parser.h"

#define POST_MB_URL "devcent601.ixtelecom.com:4545/ivr/pin"
#define GET_MB_URL "devcent601.ixtelecom.com:4545/ivr/pin/123"
#define REQUEST_DAT "{ \"vars\": { \"pin\": \"12345678901\", \"ctlnum\": \"43214321432\" } }"

int main()
{
  TagValue_t* res = NULL;

  void* client;
  client = getClientObj();

  char resp[1024*10];
  memset(resp, 0, sizeof(resp));

  char err[1024];
  memset(err, 0, sizeof(err));

  int code;

  printf("MB POST test\n");

  code = httpRequest(client, JSON, POST, POST_MB_URL, REQUEST_DAT, resp, sizeof(resp), err, sizeof(err));
  if(code==200)
  {
    int cnt = parseJsonResponse(resp, &res, "POST");
    if(cnt < 0)
      printf("FAIL\n");

    int r = 0;
    for (r=0; r < cnt; r++)
      printf("%s\t%s\n", res[r].tag, res[r].value);

    clearTVarr(res, cnt);
    res = NULL;
  }
  else
    printf("%s RET = %d\n", resp, code);

  printf("\nMB GET test\n");

  code = httpRequest(client, NO_BODY, GET, GET_MB_URL, "", resp, sizeof(resp), err, sizeof(err));
  if(code==200)
  {
    int cnt = parseJsonResponse(resp, &res, "GET");
    if(cnt < 0)
      printf("FAIL\n");

    int r = 0;
    for (r=0; r < cnt; r++)
      printf("%s\t%s\n", res[r].tag, res[r].value);

    clearTVarr(res, cnt);
    res = NULL;
  }
  else
    printf("%s RET = %d\n", resp, code);

  destroyClientObj(client);
  return 0;
}