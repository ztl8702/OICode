

using System;

namespace Codeforces {

    class Chess {

        static int N;
        static int numCount;
        static int[] an = new int[2000];


        static void ReadData() {
            Int32.TryParse(Console.ReadLine(), out N);
            var line = Console.ReadLine().Split(new char[]{' '});
            numCount = line.Length;
            for (int i = 1; i <= numCount; ++i)
            {
                Int32.TryParse(line[i-1], out an[i]);
            }
        }

        static int TrySolve(int color) {
            var result = 0;
            for (int i = 1; i<=numCount; ++i) {
                var loc = (i*2) - color;
                result += Math.Abs(an[i]-loc);    
            }
            return result;
        }
        
        static void Main(string[] args) {
            ReadData();
            Array.Sort(an,1,numCount);
            Console.WriteLine(Math.Min(TrySolve(0), TrySolve(1)));
        }

    }
}
