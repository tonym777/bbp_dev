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
	int x = 0, y = 0 ;
	vector<Point> path;
	vector<Point> return_path;

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


    int len = forth.length();
    Point p = len > 0 ? path.back() : Point(0,0);
    int running_x = p.x, running_y = p.y;


    // stand and end is the same, no moving
    if (x == 0 && y == 0) {
    	return result;
    }


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
