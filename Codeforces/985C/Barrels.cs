using System;
using System.Collections.Generic;


/**
    The problem can be re-formulated as:
       Given a list of sorted numbers a[1..m],
       find n locations (subscripts) such that
       the difference between a[last location] and a[first location] is not
       greater than l;
       distance between two locations is not greater than k;
       and the first location must be 1.

       Maximise the sum of a[locations].

       Greediness here: always push the locations as far behind as possible (when
       possible, choose larger locations)
 */
namespace Codeforces
{
    class Barrels {
        
        static int n, k,l;
        static int m;
        static int[] a = new int[100000+5];

        //static bool[] vst  = new bool[100000+5];
        //static long[] f = new long[100000+5][100000+5];


        static long Greedy() {
            long sum = 0;
            sum += a[1];
            int lastLocation = 1;
            int lastAcceptableLocation = 0;
            for (int i = 2; i<=m; ++i) {
                if (a[i]-a[1] <=l) {
                    lastAcceptableLocation = i;
                } else {
                    break;
                }
            }
            for (int i = 2; i<=n; ++i) {
                // building barrel #i
                var leftToBuild = n-i;
                var maxLocation = lastAcceptableLocation - leftToBuild ;
                
                var thisLocation = 
                  Math.Min(maxLocation, lastLocation + k);
                if (thisLocation <=lastLocation) {
                    return 0;
                }
                // Console.WriteLine($"{i}: {a[thisLocation]}");
                sum += (long) a[thisLocation];
                lastLocation = thisLocation;
            }
            return sum;
        }

        static void ReadInput() {
            var firstLine = Console.ReadLine().Split(new char[]{' '});
            Int32.TryParse(firstLine[0], out n);
            Int32.TryParse(firstLine[1], out k);
            Int32.TryParse(firstLine[2], out l);
            m = n*k;

            var secondLine = Console.ReadLine().Split(new char[]{' '});
            for (int i = 0; i < m; ++i) {
                Int32.TryParse(secondLine[i], out a[i+1]);
            }


        }
        


        static void Main(string[] args) {
            ReadInput();
            Array.Sort(a,1,m);
            Console.WriteLine(Greedy());
        }

    }
}
