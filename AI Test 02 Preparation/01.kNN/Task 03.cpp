//LC 658. Find K Closest Elements

struct res
{
    int dist;
    int point;
};
bool compareByRes(const res&a,const res&b)
{
   if (a.dist != b.dist) return a.dist < b.dist;
   return a.point < b.point;
}

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<res>result;
        for(int i=0;i<arr.size();i++)
        {
            res r;
            r.dist=abs(arr[i]-x);
            r.point=arr[i];
            result.push_back(r);
        }
        sort(result.begin(),result.end(),compareByRes);
        vector<int>resPoint;
        for( int i=0;i<k;i++)
        {
            resPoint.push_back(result[i].point);
        }
        sort(resPoint.begin(),resPoint.end());
        return resPoint;

    }
};
