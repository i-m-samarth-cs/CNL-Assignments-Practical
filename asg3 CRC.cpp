//============================================================================
// Name        : crc.cpp
// Author      : 
// Assignment  : 3
// Problem     : Write a program for error detection for 7/8 bits ASCII codes using CRC.
// Description : CRC error detection
//============================================================================

#include <iostream>
using namespace std;

int main() {

	int i,j,k;
	cout << "!!!CRC ERROR DETECTION!!!" << endl;

	    //Get Frame
	    int fs; //frame size
	    cout<<"\n Enter Size of data: ";
	    cin>>fs;

	    int f[20]; //frame data

	    cout<<" Enter data:";
	    for(i=0;i<fs;i++)//to read in frame data
	    {
	        cin>>f[i];
	    }

	    //Get Generator
	    int gs; //generator size
	    cout<<"\n Enter generator key size: ";
	    cin>>gs;

	    int g[20]; //generator or divisor data

	    cout<<"\n Enter generator key:";
	    for(i=0;i<gs;i++)
	    {
	        cin>>g[i];
	    }

	    cout<<"\n\n ::Sender Side::";
	    cout<<"\n data: ";
	    for(i=0;i<fs;i++) //print frame
	    {
	        cout<<f[i];
	    }
	    cout<<"\n key :";
	    for(i=0;i<gs;i++) //print generator/divisor
	    {
	        cout<<g[i];
	    }

	    //Append 0's before binary division
	    int rs = gs-1; //remainder size

	    cout<<"\n Number of 0's to be appended: "<<rs;
	    for (i=fs;i<fs+rs;i++) //append zeros in frame
	    {
	        f[i]=0;
	    }

	    int temp[20];
	    for(i=0;i<20;i++)//copy frame[] in temp[] for division purpose
	    {
	        temp[i]=f[i];
	    }

	    cout<<"\n Message after appending 0's :";
		for(i=0; i<fs+rs;i++)//print frame with appended zeros
		{
			cout<<temp[i];
		}

	    //binary Division
	    for(i=0;i<fs;i++)
	    {
	        j=0; //beginning pos in generator
	        k=i; //current bit pos in temp
	        //check whether it is divisible or not
	        if (temp[k]>=g[j])
	        {
	            for(j=0,k=i;j<gs;j++,k++)
	            {
	                if((temp[k]==1 && g[j]==1) || (temp[k]==0 && g[j]==0))
	                {
	                    temp[k]=0;
	                }
	                else
	                {
	                    temp[k]=1;
	                }
	            }
	        }
	    }

	    //CRC
	    int crc[15];
	    for(i=0,j=fs;i<rs;i++,j++)//copy last remainder bits as CRC
	    {
	        crc[i]=temp[j];
	    }

	    cout<<"\n CRC bits: ";
	    for(i=0;i<rs;i++) //print CRC
	    {
	        cout<<crc[i];
	    }

	    cout<<"\n Transmitted Frame: ";
	    int tf[15]; //f[]+crc[]
	    for(i=0;i<fs;i++)
	    {
	        tf[i]=f[i];
	    }
	    for(i=fs,j=0;i<fs+rs;i++,j++)
	    {
	        tf[i]=crc[j];
	    }
	    for(i=0;i<fs+rs;i++)//print transmitted frame
	    {
	        cout<<tf[i];
	    }

	    cout<<"\n\n ::Receiver side :: ";
	    cout<<"\n Received Frame: ";
	    for(i=0;i<fs+rs;i++) //print received frame
	    {
	        cout<<tf[i];
	    }

	    for(i=0;i<fs+rs;i++) //copy tf[] in temp[] for division purpose
	    {
	        temp[i]=tf[i];
	    }

	    //Division
	    for(i=0;i<fs;i++)
	    {
	        j=0;
	        k=i;
	        if (temp[k]>=g[j])
	        {
	            for(j=0,k=i;j<gs;j++,k++)
	            {
	                if((temp[k]==1 && g[j]==1) || (temp[k]==0 && g[j]==0))
	                {
	                    temp[k]=0;
	                }
	                else
	                {
	                    temp[k]=1;
	                }
	            }
	        }
	    }

	    cout<<"\n Remainder: ";
	    int rrem[15]; //
	    for (i=fs,j=0;i<fs+rs;i++,j++)
	    {
	        rrem[j]= temp[i];
	    }
	    for(i=0;i<rs;i++)
	    {
	        cout<<rrem[i];
	    }

	    int flag=0;
	    for(i=0;i<rs;i++)
	    {
	        if(rrem[i]!=0)
	        {
	            flag=1;
	            break;
	        }
	    }

	    if(flag==0)
	    {
	        cout<<"\n Since Remainder Is 0 Hence Message Transmitted From Sender To Receiver Is Correct";
	    }
	    else
	    {
	        cout<<"\n Since Remainder Is Not 0 Hence Message Transmitted From Sender To Receiver Contains Error";
	    }

	return 0;
}

/*
 * SAMPLE OUTPUT 1:
 *
!!!CRC ERROR DETECTION!!!

 Enter Size of data: 10
 Enter data:1 1 0 1 0 1 1 0 1 1

 Enter generator key size: 5
 Enter generator key:1 0 0 1 1


 ::Sender Side::
 data: 1101011011
 key :10011
 Number of 0's to be appended: 4
 Message after appending 0's :11010110110000
 CRC bits: 1110
 Transmitted Frame: 11010110111110

 ::Receiver side ::
 Received Frame: 11010110111110
 Remainder: 0000
 Since Remainder Is 0 Hence Message Transmitted From Sender To Receiver Is Correct

 * SAMPLE OUTPUT 2:
 *
 !!!CRC ERROR DETECTION!!!

 Enter Size of data: 8
 Enter data:1 1 0 1 0 1 1 1

 Enter generator key size: 3
 Enter generator key:1 0 1


 ::Sender Side::
 data: 11010111
 key :101
 Number of 0's to be appended: 2
 Message after appending 0's :1101011100
 CRC bits: 00
 Transmitted Frame: 1101011100

 ::Receiver side ::
 Received Frame: 1101011100
 Remainder: 00
 Since Remainder Is 0 Hence Message Transmitted From Sender To Receiver Is Correct
*/
