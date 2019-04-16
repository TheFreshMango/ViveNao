using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using System.IO;

namespace NaoCSharpLibrary
{
    public class NaoCSharpLibrary
    {
        // From c++ Dll (unmanaged)
        [DllImport("sayhelloworld_d")]
        public static extern void NaoWalkTo(float x, float y, float theta);
        [DllImport("sayhelloworld_d")]
        public static extern void NaoSpeak(string phraseToSay);
        [DllImport("sayhelloworld_d")]
        public static extern void NaoWave();
        [DllImport("sayhelloworld_d")]
        public static extern void NaoSit();
        [DllImport("sayhelloworld_d")]
        public static extern void NaoStand();
        [DllImport("sayhelloworld_d")]
        public static extern void NaoLieDown();
        [DllImport("sayhelloworld_d")]
        public static extern void SubscribeVideo();
        [DllImport("sayhelloworld_d")]
        public static extern int GetImageData(out IntPtr data, out int size, out int width, out int heigth);
        [DllImport("sayhelloworld_d")]
        public static extern void UnsubscribeVideo();
        [DllImport("sayhelloworld_d")]
        public static extern string GetIPAddress();
        [DllImport("sayhelloworld_d")]
        public static extern void SetIPAddress(string ipAddress);


        //public static Bitmap GetDataPicture(int width, int height, byte[] arr)
        //{

        //    var output = new Bitmap(width, height, PixelFormat.Format24bppRgb);
        //    var rect = new Rectangle(0, 0, width, height);
        //    var bmpData = output.LockBits(rect, ImageLockMode.ReadWrite, output.PixelFormat);

        //    Row - by - row copy
        //       var arrRowLength = width * Image.GetPixelFormatSize(output.PixelFormat) / 8;
        //    IntPtr ptr = bmpData.Scan0;
        //    for (var i = 0; i < height; i++)
        //    {
        //        Marshal.Copy(arr, i * arrRowLength, ptr, arrRowLength);
        //        ptr = new IntPtr(ptr.ToInt64() + bmpData.Stride);
        //    }

        //    output.UnlockBits(bmpData);
        //    return output;
        //}



        public static IntPtr GetRawPictureIntPtr(out int size)
        {
            IntPtr adr;
            int width;
            int height;
            size = 0;
            try
            {
                if (GetImageData(out adr, out size, out width, out height) == 0)
                    return IntPtr.Zero;
                return adr;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                return IntPtr.Zero;
            }
        }

        public static byte[] GetRawPictureByte()
        {
            try
            { 
                IntPtr adr;
                int size;
                int width;
                int height;

                if (GetImageData(out adr, out size, out width, out height) == 0)
                    return null;

                byte[] data = new byte[size];
                Marshal.Copy(adr, data, 0, data.Length);

                return data;
            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
                return null;
            }
        }
        //static void Main(string[] args)
        //{
        //    Console.WriteLine(GetIPAddress());
        //    SetIPAddress("123.1.2");
        //    Console.WriteLine(GetIPAddress());
        //}
        //{

            //    try
            //    {
            //        SubscribeVideo();
            //        IntPtr adr;
            //        int size;
            //        int width;
            //        int height;
            //        if (GetImageData(out adr, out size, out width, out height) == 0)
            //        {
            //            return;
            //        }
            //        byte[] data = new byte[size];
            //        Marshal.Copy(adr, data, 0, data.Length);
            //        GetDataPicture(width, height, data).Save("Foo.jpeg", ImageFormat.Jpeg);
            //        //Console.WriteLine(Encoding.Default.GetString(data));

            //    }
            //    catch (Exception e)
            //    {
            //        Console.WriteLine(e.ToString());
            //    }
            //    try
            //    {
            //        UnsubscribeVideo();
            //    }
            //    catch (Exception e)
            //    {
            //        Console.WriteLine(e.ToString());
            //    }

            //    Console.ReadKey();
            //}

        }
}
