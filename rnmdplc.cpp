#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_selection.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <vector>
#include <experimental/random>
#include <CGAL/intersections.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Rect_2;
typedef K::Circle_2 Circle_2;
typedef CGAL::Convex_hull_traits_adapter_2<K,
    CGAL::Pointer_property_map<Point_2>::type > Convex_hull_traits_2;


Rect_2 doRmdObj()
{
    int top_xrand = std::experimental::randint(1, 5);
    int top_yrand = std::experimental::randint(1, 5);

    Rect_2 rect = Rect_2(Point_2(0,0), Point_2(top_xrand,top_yrand));
    return rect;
}

Circle_2 getCircle() {
    const double square = 10.0;
    Circle_2 circle = Circle_2(Point_2(0,0), square);

    CGAL::Bbox_2 bounding = circle.bbox();
    std::cout << "Bounding:" << bounding << std::endl;

    return circle;
}


std::vector<Rect_2> getObj(std::vector<Rect_2> in ,int n)
{
    for (int i = 0; i < n; ++i)
    {
        in.push_back(doRmdObj());
    }
    return in;
}

Point_2 getRmdLoc(int xmin, int xmax, int ymin, int ymax){
    return Point_2(std::experimental::randint(xmin, xmax), std::experimental::randint(ymin, ymax));
}


std::vector<Rect_2> adjustPosition(std::vector<Rect_2> rect_list) {

    for (int i = 0; i < rect_list.size(); i++) {

        int new_x = std::experimental::randint((int)rect_list.at(i).xmax(), 30);
        int new_y = std::experimental::randint((int)rect_list.at(i).ymax(), 10);
        
        Point_2 n_min_Point = Point_2(new_x - rect_list.at(i).xmax(), new_y - rect_list.at(i).ymax());
        Point_2 n_max_Point = Point_2(new_x, new_y);

        Rect_2 new_rect = Rect_2(n_min_Point, n_max_Point);

        rect_list.at(i) = new_rect;
    }

    for (Rect_2 rect : rect_list) {
        for (int i = 0; i < rect_list.size(); ++i)
        {
            if (CGAL::do_intersect(rect, rect_list[i])) {
                int r {}; //ToDo: Rect_2 doesnt have to intersect
            }
        }
    }
    return rect_list;
}

Circle_2 getRmdLocOnMapCrcl(Circle_2 crcl, const double square) {
    Point_2 loc = getRmdLoc(0, 30, 0, 10);
    return Circle_2(loc, square);
}


bool isIntersected(Circle_2 placable_circle, std::vector<Rect_2> rects, std::vector<Circle_2> circles) {
    for (Rect_2 rect : rects) {
        if (CGAL::do_intersect(placable_circle, rect)) return true;
    
    }
    std::cout << "No intersection with Rects" << std::endl;
    std::cout << "Circle Pos:" << placable_circle.bbox() << ", square:" << placable_circle.squared_radius() << std::endl;
    return false;

}


int main()
{
    std::vector<Rect_2> outer_section_map = { Rect_2(Point_2(0,0), Point_2(-1, 10)),
                                          Rect_2(Point_2(0,10), Point_2(30, 11)),
                                          Rect_2(Point_2(30,0), Point_2(31, 10)),
                                          Rect_2(Point_2(0,0), Point_2(30, -1)) };


    std::vector<Rect_2> rect_list = getObj(rect_list, 4);
    for (auto& rect : rect_list) std::cout << rect << std::endl;
    
    rect_list = adjustPosition(rect_list);
    for (auto& rect : rect_list) std::cout << rect << std::endl;

    rect_list.insert(rect_list.end(), outer_section_map.begin(), outer_section_map.end());

    std::cout << rect_list.size() << std::endl;
    Circle_2 place_obj_crcl= getCircle();

    double square = 10.0;    
    
    bool cond_Var = true;
    int mk_crcl_smaller = 0;

    while (cond_Var) {

        if (mk_crcl_smaller%10)
        {
            square -= 1.0;
        }
        
        place_obj_crcl = getRmdLocOnMapCrcl(place_obj_crcl, square);
        cond_Var = isIntersected(place_obj_crcl, rect_list, {});
        mk_crcl_smaller++;
    }
    

    return 0;
}