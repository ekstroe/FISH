#include "fisharduino.h"

int charcounter(const char* filename, int line) {
    FILE* file = fopen(filename, "r");
    int counter = 0;
    int size = 0;
    int counter2 = 0;
    if (!file)
    {
        return -1;
    }
    else
    {
        //get size of first line
        int c;
        while (((c = getc(file)) != '\n'))
        {
            if ((c == ':') || (isspace(c) ))
            {
                continue;
            }
            else
            {
                counter++;
            }
        }
        //get size of second line
        while (((c = getc(file)) != '\n'))
        {
            if ((c == ':') || (isspace(c) ))
            {
                continue;
            }
            else
            {
                counter2++;
            }
        }
        //get size of whole file
        rewind(file);
        while (((c = getc(file)) != EOF))
        {
            if ( (c == ':') || (c == '\n') || (isspace(c)) )
            {
                continue;
            }
            else
            {
                size++;
            }
        }
        //return based on line
        if (line == 1)
        {
            return (counter / 4);
        }
        if (line == 2)
        {
            return (counter2 / 2);
        }
        if (line == 3)
        {
            return ((size - (counter + counter2)) / 4);
        }
        else
        {
            return -1;
        }
    }
}

int static retsecs(char* str, int size)
{
    int ret = 0;
    if (size == 6)
    {
        ret += ((str[0] - '0')*60*10 + (str[1] - '0')*60) * 100;
        ret += ((str[3] - '0')*10 + (str[4] - '0')) * 100;
        return ret;
    }
    if (size == 3)
    {
        ret += ((str[0] - '0')*10 + (str[1] - '0')) * 100;
        return ret;
    }
}

int initsong(SONG* Song, const char* filename) {
    int ssc = charcounter(filename, 1);
    int smt = charcounter(filename, 2);
    int sfc = charcounter(filename, 3);
    FILE* file = fopen(filename, "r");
    if (!file || (ssc == -1) || (sfc == -1))
    {
        return 0;
    }
    else
    {
        Song->song = (long long*) malloc((ssc+1) * sizeof(long long));
        Song->mtime = (int*) malloc((smt+1) * sizeof(int));
        Song->flip = (long long*) malloc((sfc+1) * sizeof(long long));
        //parse trough file to find times to open mouth / flip tail
        char str[7];
        int counter = 0;
        int counter2 = 0;
        int counter3 = 0;
        while ((counter < ssc) && (fgets(str, 7, file) != NULL))
        {
            (Song->song)[counter] = retsecs(str,6);
            counter++;
        }
        while ((counter < ssc + smt) && (fgets(str, 4, file) != NULL))
        {
            (Song->mtime)[counter2] = retsecs(str,3);
            counter++;
            counter2++;
        }
        while ((counter < (ssc + smt + sfc + 1)) && (fgets(str, 7, file) != NULL))
        {
            (Song->flip)[counter3] = retsecs(str,6);
            counter++;
            counter3++;
        }
        Song->song[ssc] = -1;
        Song->mtime[smt] = -1;
        Song->flip[sfc] = -1;
        fclose(file);
        return 1;
    }
}

void freeSong(SONG* Song)
{
    free(Song->song);
    free(Song->mtime);
    free(Song->flip);
}


//open Mouth
void openmouth(int pin, long long duration)
{
  pinMode(pin, HIGH);
  unsigned long startime = millis();
  while((millis() - starttime) < duration)
  {
    // do Nothing
  }
  pinMode(pin, LOW);
}

void fliptail(Servo servo, int duration, int top, int bottom)
{
  servo.write(top);
  unsigned long startime = millis();
  while((millis() - starttime) < duration)
  {
    // do Nothing
  }
  servo.write(bottom);
}

int checkptr(int check)
{
  if (check == -1)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

