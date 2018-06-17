/*************************************************************************
'b' is the base
'e' is the exponent

This function will return the answer of b^e ('b' to the power of 'e')
*************************************************************************/

int pow(int b,int e)
{
  int ans = 1;
  
  for (int i = 1; i <= e; i++)
    ans *=b;
 
  return ans;
}

/*************************************************************************
"av" is the user's input
This function will get the absolute value of a double
*************************************************************************/

double fabs(double av)
{
  if (av < 0)
    {
      av = (av*0) - av;
    }
  else
    {
      av = (av*0) + av;
    }
  return av;
}

/*************************************************************************
"rd" is the user's input
This function will round the user's input up/down into an integer
*************************************************************************/

int round(double rd)
{
  if (rd > 0)
    {
      rd = int(rd + 0.5);
    }
  else if (rd < 0)
    {
      rd = int(rd - 0.5);
    }
  return rd;
}

/*************************************************************************
"prime" is the user's input in which we are checking if it is prime
This function will take the user's input and see if it is divisble by itself 
*************************************************************************/

int isPrime(int num)
{
  bool prime = true;

  for (int i = 2; i <= num / 2; ++i)
    { 
      if (num % i == 0) //If the number itself divided by two equates to a remander of zero, it is not prime.
	{
	  prime = false;
	}
    }
  return prime;
}
/*************************************************************************
Square Root blah blah
*************************************************************************/

int square(int top) 

{
  int input = 0;

  for (int i = 1; i < i + 1; i++)
    {
      if ( (i*i) >= input)
	{
	  if ((i*i) == input)
	    {
	      top = i;
	    }
	  else
	    {
	      top = i;
	    }
	}
    }

  return top;
}


