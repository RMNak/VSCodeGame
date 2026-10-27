using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Expressions;
using System.Security;
using System.Runtime.InteropServices;
using System.Text;

class Program
{
    public static void SecureStringToByteArray(IntPtr userptr, IntPtr pwdptr, SecureString userStr, SecureString pwdStr, ref byte[] plaintext)
    {
        userptr = Marshal.SecureStringToGlobalAllocUnicode(userStr);
        pwdptr = Marshal.SecureStringToGlobalAllocUnicode(pwdStr);
        IntPtr colon = Marshal.StringToBSTR(":");
        int lengthOfString = userStr.Length + pwdStr.Length + 1;
        plaintext = new byte[lengthOfString * 2];
        int i = 0;
        for (; i < userStr.Length; i++)
        {
            plaintext[i] = (byte)Marshal.ReadInt16(userptr, i * 2);
        }

        plaintext[i++] = (byte)Marshal.ReadInt16(colon, 0);

        Console.WriteLine("User1 : " + Encoding.ASCII.GetString(plaintext) + " ---> " + i);

        for (int j = 0; j < pwdStr.Length; j++)
        {
            plaintext[i + j] = (byte)Marshal.ReadInt16(pwdptr, j * 2);
            Console.WriteLine("User : " + Encoding.ASCII.GetString(plaintext) + " ---> " + (i + j));
        }

        Console.WriteLine("User byte : " + Convert.ToBase64String(Encoding.Convert(Encoding.Default, Encoding.GetEncoding("ISO-8859-1"), plaintext)));
        
        /*unsafe
        {
            // Copy without null bytes
            byte* bstr = (byte*)userptr;
            int i = 0;
            for (; i < userStr.Length; i++)
            {
                byte[] temp = new byte[1]; 
                temp[0] = *bstr;
                Console.WriteLine("User before byte : " + Encoding.UTF8.GetString(temp));

                plaintext[i] = *bstr++;
                Console.WriteLine("User : " + Encoding.ASCII.GetString(plaintext));// Copy a single byte to a temporary array for display

                temp[0] = *bstr;
                Console.WriteLine("User middle byte : " + Encoding.UTF8.GetString(temp));

                *bstr = *bstr++;  
                temp[0] = *bstr;
                Console.WriteLine("User after byte : " + Encoding.UTF8.GetString(temp));
            }
            {
                bstr = (byte*)colon;
                plaintext[i] = *bstr++;
                Console.WriteLine("User : " + Encoding.ASCII.GetString(plaintext));
                byte[] temp = new byte[1];
                temp[0] = *bstr;
                Console.WriteLine("User byte : " + Encoding.UTF8.GetString(temp));

            }


            bstr = (byte*)pwdptr;
            for (++i; i < lengthOfString; i++)
            {
                plaintext[i] = *bstr++;
                Console.WriteLine("User : " + Encoding.ASCII.GetString(plaintext));
                *bstr = *bstr++;
                byte[] temp = new byte[1];
                temp[0] = *bstr;
                Console.WriteLine("User byte : " + Encoding.UTF8.GetString(temp));
            }
        } */
    }
        
    static void Main()
        {
        string user = "username";
        string password = "password"; 
        SecureString secureUserString = new SecureString();
        user.ToCharArray().ToList().ForEach(p => secureUserString.AppendChar(p));
        SecureString securePwdString = new SecureString();
        password.ToCharArray().ToList().ForEach(p => securePwdString.AppendChar(p));

        byte[] plaintext = null;
        GCHandle gcHandle = GCHandle.Alloc(plaintext, GCHandleType.Pinned);
        IntPtr unmanagedUserPtr = IntPtr.Zero;
        IntPtr unmanagedPwdPtr = IntPtr.Zero;

        SecureStringToByteArray(unmanagedUserPtr, unmanagedPwdPtr, secureUserString, securePwdString, ref plaintext);
            // Create a constant expression with an integer value
        /*ConstantExpression constExprInt = Expression.Constant(42);
            Console.WriteLine("Constant Expression (int):");
            Console.WriteLine("Type: " + constExprInt.Type);
            Console.WriteLine("Value: " + constExprInt.Value);
            Console.WriteLine();

            // Create a constant expression with a string value
            ConstantExpression constExprString = Expression.Constant("Hello, World!");
            Console.WriteLine("Constant Expression (string):");
            Console.WriteLine("Type: " + constExprString.Type);
            Console.WriteLine("Value: " + constExprString.Value);
            Console.WriteLine();

            // Create a constant expression with a double value
            ConstantExpression constExprDouble = Expression.Constant(3.14159);
            Console.WriteLine("Constant Expression (double):");
            Console.WriteLine("Type: " + constExprDouble.Type);
            Console.WriteLine("Value: " + constExprDouble.Value);
            Console.WriteLine();

            // Create a constant expression with a boolean value
            ConstantExpression constExprBool = Expression.Constant(true);
            Console.WriteLine("Constant Expression (bool):");
            Console.WriteLine("Type: " + constExprBool.Type);
            Console.WriteLine("Value: " + constExprBool.Value);
            Console.WriteLine(); */
        }
}