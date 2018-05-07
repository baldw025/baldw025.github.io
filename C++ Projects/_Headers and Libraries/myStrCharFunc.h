//////////##### myStrCharFunc.h #####//////////

//String Copy, copies characters to other char datatypes
void myStrcpy(char dest[], const char source[])
{
  int i = 0;

  for(i = 0; source[i] != '\0'; i++)
    {
      dest[i] = source[i];
    }

  dest[i] = '\0';
}

char myToUpper(char i)
{
  if(i >= 'a' && i <= 'z')
    {
      i -= 32;
    }

  return i;
}

int myStrlen(char ar[])
{
  int counter = 0;

  for(int i = 0; ar[i] != '\0'; i++)
    {
      counter++;
    }

  return counter;
}
