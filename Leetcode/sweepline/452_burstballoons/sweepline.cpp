class Solution {
public:
    /*
    graphical illustration
    [[10,16],[2,8],[1,6],[7,12]]
 Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
 Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12]

 if the distance of a line that is in the direction of y axis to the center of a circle is less than the radius of that circle, that line passes the circle and burst the baloon. as the center of [2,8] lies on x=5, the min distance between x=6 is 1, which is less than the radius 3, so x = 6 can burst [2,8]. Instead the center of [7,12] lies on x = 9.5, the distance between x=6 is 3.5, which is larger than the radius 2.5, so x=6 can't burst it. So, if the x value of the arrow falls in the range of the diameter, it can burst the balloon. Meanwhile, if the diameter arrays of two balloon collapse with each other, they can be bursted by one arrow. So we can convert the question into - how many minimum combined array we can have for the question array.

    |         *
    |         *  [2,8]
    |         *             。[7,12]
    |  ****************     。
    |         *             。           +
    |         *             。           + [10,16]
    |         *       。。。。。。。。。  +
    |       x               。           +
    |       x               。  ++++++++++++++++++++
    |       x               。           +
    |xxxxxxxxxxxxxxxx       。           +
    |       x                            +
    |       x    [1,6]                   +
     _  _  _x_  _  _  _  _  _  _  _  _  _  _  _  _  _  _
     1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18
    */

    int findMinArrowShots(vector<vector<int>>& points) {
        //sort the vector<vector<int>> according to the ending value of each <vector<int>
        sort(points.begin(), points.end(), [](auto& a, auto& b) {
            return a[1] < b[1];
            });
        /*
        the example can be visualized as
        [1     6]
          [2       8]
                 [7      12]
                     [10        16]
        if we want to cover first range, we have to draw a line from x = 6
        we can check how many ranges this line can pass and remove those ranges
        we will start from the next range which can't be covered by this line
        */
        //sweep line
        int cur = 0;
        int arrow = 0;
        while (cur < points.size()) {
            arrow++;
            int next = cur + 1;
            for (int i = cur + 1; i < points.size(); i++) {
                if (points[i][0] > points[cur][1]) { // the line can't pass this range
                    break;
                }
                else {
                    next = i + 1;
                }
            }
            cur = next;
            //cout << cur << "," << next  << "." << arrow << endl;
        }
        return arrow;
    }

};