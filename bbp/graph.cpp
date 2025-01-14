#include <bits/stdc++.h>
#include <limits.h>

using namespace std;

struct Point {
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}

	int x;
	int y;
};


vector<Point> build_graph(string &forth) {
	int x = 0, y = 0 ;
	vector<Point> path;

    for (char c : forth) {
        switch (c) {
        case 'N':
        	y++;
            break;
        case 'S':
        	y--;
            break;
        case 'E':
        	x++;
            break;
        case 'W':
        	x--;
            break;
        }

    	path.emplace(path.end(), x, y);
    }
    return path;
}

bool hasIntersect(Point newPoint , vector<Point> path, vector<Point> return_path) {

	for ( Point p : path ) {
		if ( newPoint.x == p.x && newPoint.y == p.y ) {
			return true;
		}
	}

	for ( Point p : return_path ) {
		if ( newPoint.x == p.x && newPoint.y == p.y ) {
			return true;
		}
	}

	return false;
}

string solution_path(string &forth) {
    string result;
    int x_min = INT_MAX, x_max = INT_MIN;
    int y_min = INT_MAX, y_max = INT_MIN;
	int x = 0, y = 0 ;
	vector<Point> path = build_graph(forth);
	vector<Point> return_path;


    int len = forth.length();
    Point p = path.back();
    int running_x = p.x, running_y = p.y;

    for (int i = forth.size()-1; i >= 0; i--)  {
    	bool move = false;
    	char lastDirection = result.length() > 0 ? result.back() : forth[len-1];

    	if ( abs(running_x-1)+abs(running_y) < abs(running_x)+abs(running_y) && lastDirection != 'E' ) {
    		if ( move == false && hasIntersect(Point(running_x-1, running_y), path, return_path) == false ) {
    			result.append("W");
    			running_x--;
    			move = true;
    		}
    	}
    	if ( abs(running_x+1)+abs(running_y) < abs(running_x)+abs(running_y) && lastDirection != 'W' ) {
    		if ( move == false && hasIntersect(Point(running_x+1, running_y), path, return_path) == false ) {
    			result.append("E");
    			running_x++;
    			move = true;
    		}
    	}
    	if ( abs(running_x)+abs(running_y-1) < abs(running_x)+abs(running_y) && lastDirection != 'N' ) {
    		if ( move == false && hasIntersect(Point(running_x, running_y-1), path, return_path) == false ) {
    			result.append("S");
    			running_y--;
    			move = true;
    		}

    	}
    	if (  abs(running_x)+abs(running_y+1) < abs(running_x)+abs(running_y) && lastDirection != 'S' ) {
    		if ( move == false && hasIntersect(Point(running_x, running_y+1), path, return_path) == false ) {
    			result.append("N");
    			running_y++;
    			move = true;
    		}
    	}


    	if (move == false) {
        	if ( running_y !=0 && abs(running_x-1)+abs(running_y) > abs(running_x)+abs(running_y) && lastDirection != 'E' ) {
        		if ( move == false && hasIntersect(Point(running_x-1, running_y), path, return_path) == false ) {
        			result.append("W");
        			running_x--;
        			move = true;
        		}
        	}

        	if ( running_y !=0 && abs(running_x+1)+abs(running_y) > abs(running_x)+abs(running_y) && lastDirection != 'W' ) {
        		if ( move == false && hasIntersect(Point(running_x+1, running_y), path, return_path) == false ) {
        			result.append("E");
        			running_x++;
        			move = true;
        		}
        	}
        	if ( running_x !=0 && abs(running_x)+abs(running_y-1) > abs(running_x)+abs(running_y) && lastDirection != 'N' ) {
        		if ( move == false && hasIntersect(Point(running_x, running_y-1), path, return_path) == false ) {
        			result.append("S");
        			running_y--;
        			move = true;
        		}

        	}
        	if ( running_x !=0 && abs(running_x)+abs(running_y+1) > abs(running_x)+abs(running_y) && lastDirection != 'S' ) {
        		if ( move == false && hasIntersect(Point(running_x, running_y+1), path, return_path) == false ) {
        			result.append("N");
        			running_y++;
        			move = true;
        		}
        	}
    	}


        if (move == true) {
        	return_path.emplace(return_path.end(), running_x, running_y);
        }


        // we back to start point
        if ( running_x == 0 &&  running_y == 0 ) {
        	return result;
        }

    }

    if ( (result.back() != 'E' && hasIntersect(Point(running_x-1, running_y), path, return_path) == false )
    		|| (result.back() != 'W' && hasIntersect(Point(running_x+1, running_y), path, return_path) == false) ) {

    // end point
        // end point
        if (running_x <= 0 && running_y <= 0) {
        	if (hasIntersect(Point(running_x+1, running_y), path, return_path) == false) {
        		result.append("E");
        		running_x++;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x, running_y+1), path, return_path) == false) {
        		    result.append("N");
        		    running_y++;
        		    return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        	else if (hasIntersect(Point(running_x, running_y+1), path, return_path) == false) {
        		result.append("N");
        		running_y++;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x+1, running_y), path, return_path) == false) {
            		result.append("E");
            		running_x++;
            		return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        }

        else if (running_x <= 0 && running_y >= 0) {
        	if (hasIntersect(Point(running_x+1, running_y), path, return_path) == false) {
        		result.append("E");
        		running_x++;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x, running_y-1), path, return_path) == false) {
        		    result.append("S");
        		    running_y--;
        		    return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        	else if (hasIntersect(Point(running_x, running_y-1), path, return_path) == false) {
        		result.append("S");
        		running_y--;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x+1, running_y), path, return_path) == false) {
            		result.append("E");
            		running_x++;
            		return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        }
        else if (running_x >= 0 && running_y <= 0) {
        	if (hasIntersect(Point(running_x-1, running_y), path, return_path) == false) {
        		result.append("W");
        		running_x--;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x, running_y+1), path, return_path) == false) {
        		    result.append("N");
        		    running_y++;
        		    return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        	else if (hasIntersect(Point(running_x, running_y+1), path, return_path) == false) {
        		result.append("N");
        		running_y++;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x-1, running_y), path, return_path) == false) {
            		result.append("E");
            		running_x--;
            		return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        }
        else if (running_x >= 0 && running_y >= 0) {
        	if (hasIntersect(Point(running_x-1, running_y), path, return_path) == false) {
        		result.append("W");
        		running_x--;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x, running_y-1), path, return_path) == false) {
        		    result.append("S");
        		    running_y--;
        		    return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        	else if (hasIntersect(Point(running_x, running_y-1), path, return_path) == false) {
        		result.append("S");
        		running_y--;
        		return_path.emplace(return_path.end(), running_x, running_y);
        		if (hasIntersect(Point(running_x-1, running_y), path, return_path) == false) {
            		result.append("W");
            		running_x++;
            		return_path.emplace(return_path.end(), running_x, running_y);
        		}
        	}
        }



    return result;

}


int main()
{
return 1;
}


