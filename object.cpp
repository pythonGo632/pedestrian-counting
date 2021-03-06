/* object.cpp
 * a class that defines an object for tracking in openCV
 
 * Brian J Gravelle
 * ix.cs.uoregon.edu/~gravelle
 * gravelle@cs.uoregon.edu

 * Apparently this is something I'm supposed to do:
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:

 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.

 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.

 * If by some miracle you find this software useful, thanks are accepted in
 * the form of chocolate or introductions to potential employers.

 */

#include "object.h"
using namespace std;
using namespace cv;


/*************************** Constructors ***************************/

Object::Object() {
  id = -1;
  is_counted = false;
}

Object::Object(const vector<Point> &contour) {
  Moments temp_moment = moments(contour);
  center = Point2d(temp_moment.m10/temp_moment.m00 , temp_moment.m01/temp_moment.m00);
  id = -1;
  is_counted = false;
  box = boundingRect(contour);
}

Object::Object(const Point2d &new_center, int new_id, Rect2d &new_box) {
  center = Point2d(new_center);
  id = new_id;
  is_counted = false;
  box = Rect2d(new_box);
}

Object::Object(const Object &other) {
  other.get_center(center);
  id = other.get_id();
  is_counted = other.get_is_counted();
  other.get_box(box);
}

Object::~Object() {

}


/*************************** Other Members ***************************/

double Object::find_distance_sqd(const Point2d &other_center) const {
  Point2d diff = center - other_center;
  return (diff.x * diff.x) + (diff.y * diff.y);
}

double Object::find_distance_sqd(const Object &other_object) const {
  Point2d other_center;
  other_object.get_center(other_center);
  return find_distance_sqd(other_center);
}


bool Object::overlaps(const Object &other_object) const {
  Rect2d other_box;
  double area;

  other_object.get_box(other_box);
  area = (box & other_box).area();

  return (area > 0.0);
}


double Object::find_overlap_area(const Object &other_object) const {
  Rect2d other_box;

  other_object.get_box(other_box);
  return (box & other_box).area();
}


double Object::find_overlap_fraction(const Object &other_object) const {
  Rect2d other_box;

  other_object.get_box(other_box);
  return (box & other_box).area() / box.area();
}



/*************************** Setters ***************************/

void Object::set_center(Point2d &new_center) {
  center = Point2d(new_center);
}

void Object::set_center(vector<Point> &contour) {
  Moments temp_moment = moments(contour);
  center = Point2d(temp_moment.m10/temp_moment.m00 , temp_moment.m01/temp_moment.m00);
}

void Object::set_id(int new_id) {
  id = new_id;
}

void Object::set_is_counted(bool new_is_counted /* = true*/){
  is_counted = new_is_counted;
}

void Object::set_box(Rect2d &new_box) {
  box = Rect2d(new_box);
}

/*************************** Getters ***************************/

void Object::get_center(Point2d &out_center) const {
  out_center = Point2d(center);
}

int  Object::get_id() const {
  return id;
}

bool Object::get_is_counted() const {
  return is_counted;
}

void Object::get_box(Rect2d &out_box) const {
  out_box = Rect2d(box);
}

double Object::get_box_height(){
  return box.height;
}

double Object::get_box_width(){
  return box.width;
}