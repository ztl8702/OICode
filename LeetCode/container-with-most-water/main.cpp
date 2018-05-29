class Solution {
    
    // find >= target
    int searchToRight(const vector<int>& arr, int target, int start) {
        int left = start;
        int right = arr.size()-1;
        while (left< right) {
            int mid = (left+right+1) /2;
            int value = arr[mid];
            if (value>=target) {
                left = mid;
            } else {
                right = mid -1;
            }
        }
        // now left == right
        if (arr[left] >=target) {
            return left;
        } else {
            return -1;
        }
    }
    
    
    // find >= target
    int searchToLeft(const vector<int>& arr, int target, int start) {
        int left = 0;
        int right = start;
        while (left< right) {
            int mid = (left+right) /2;
            int value = arr[mid];
            if (value>=target) {
                right = mid;
            } else {
                left = mid +1;
            }
        }
        // now left == right
        if (arr[left] >=target) {
            return left;
        } else {
            return -1;
        }
    }
public:
    int maxArea(vector<int>& height) {
        vector<int> highestToEnd;
        vector<int> highestToStart;
        highestToEnd.resize(height.size());
        highestToStart.resize(height.size());
        highestToStart[0] = height[0];
        
        for (int i = 1; i<height.size(); ++i) {
            if (height[i] > highestToStart[i-1]) {
                highestToStart[i] = height[i];
            } else {
                highestToStart[i] = highestToStart[i-1];
            }
        }
        
        highestToEnd[height.size()-1] = height[height.size()-1];
        for (int i =height.size()-2 ; i>=0; --i) {
            if (height[i] > highestToEnd[i+1]) {
                highestToEnd[i] = height[i];
            } else {
                highestToEnd[i] = highestToEnd[i+1];
            }
        }
        
        
        long long maxA = 0LL;
        for (int i = 0; i< height.size(); ++i) {
            if (i>0) {
                int leftHighest = searchToLeft(highestToStart, height[i],i-1 );
                if (leftHighest!=-1) {
                    long long newA = (i-leftHighest)*height[i];
                    if (newA>maxA) maxA=newA;
                }
            }
            
            if (i<height.size()-1) {
                int rightHighest = searchToRight(highestToEnd, height[i],i+1);
                if (rightHighest!=-1) {
                    long long newA = (rightHighest-i)*height[i];
                    if (newA>maxA) maxA=newA;
                }
            }
        }
        
        return (int) maxA;
        
    }
};
