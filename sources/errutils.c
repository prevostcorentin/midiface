#include <headers/errutils.h>
#include <stdio.h>


int midifile_errors[MAX_ERRORS]={MIDIFILE_OK};
int err_count=0;


int midifile_get_last_error()
{
   int error=midifile_errors[0];
   for(int i=0; i < err_count; i++) {
      midifile_errors[i] = midifile_errors[i + 1];
   }
   if(err_count >= 0) {
      err_count = err_count - 1;
   }
   return error;
}

void midifile_add_error(int code)
{
   midifile_errors[err_count] = code;
   err_count = err_count + 1;
}
