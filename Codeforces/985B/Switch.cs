using System;

/*
    This problem is a nice demonstration of time complexity.
    O(n^2) works but O(n^3) won't.
 */
namespace Codeforces
{
    class Switch {
        
        static int n, m;
        static bool[,] map;

        static bool CanOmitAny() {
            for (int i = 1; i<=n; ++i) {
                // omit switch i
                bool[] tmp = new bool[m+1];
                for (int j=1 ;j<=n;++j) {
                    if (j!=i) {
                        for (int k = 1; k<=m;++k) {
                            tmp[k] = tmp[k] || map[j,k];
                        }
                    }
                }

                var canOmit = true;
                for (int j=1;j<=m; ++j) {
                    if (tmp[j] == false) {
                        canOmit = false;
                        break;
                    }
                }
                
                if (canOmit) {
                    return true;
                }
            }
            return false;
        }

        static bool CanOmitAnyFast() {
            var canOmit = new bool[n+1];
            for (int i = 1; i<=n; ++i) {
                canOmit[i] = true;
            }

            for (int i = 1; i<=m;++i) {
                int switchCount = 0;
                int switchIndex = -1;
                for (int j = 1; j<=n; ++j) {
                    if (map[j,i]) {
                        switchCount++;
                        switchIndex = j;
                        if (switchCount > 1) {
                            break;
                        }
                    }
                }
                if (switchCount == 1) {
                    canOmit[switchIndex] = false;
                }
            }
            
            for (int i =1; i<=n; ++i) {
                if (canOmit[i]) return true;
            }
            return false;
        }

        static void Main(string[] args) {
            var firstLine = Console.ReadLine().Split(new char[]{' '});
            Int32.TryParse(firstLine[0], out n);
            Int32.TryParse(firstLine[1], out m);

            map = new bool[n+1,m+1];

            for (int i = 1; i<=n; ++i) {
                var line = Console.ReadLine();
                for (int j = 1; j<=m; ++j) {
                    map[i,j] = line[j-1] == '1';
                }
            }

            Console.WriteLine(CanOmitAnyFast() ? "YES" : "NO");


        }

    }
}
