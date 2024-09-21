#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_selection.h>
#include <CGAL/Convex_hull_traits_adapter_2.h>
#include <CGAL/property_map.h>
#include <vector>
#include <experimental/random>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Iso_rectangle_2 Rect_2;
typedef K::Circle_2 Circle_2;
typedef CGAL::Convex_hull_traits_adapter_2<K,
    CGAL::Pointer_property_map<Point_2>::type > Convex_hull_traits_2;


Rect_2 do_rmd_obj()
{
    int top_xrand = std::experimental::randint(1, 5);
    int top_yrand = std::experimental::randint(1, 5);

    Rect_2 rect = Rect_2(Point_2(0,0), Point_2(top_xrand,top_yrand));
    return rect;
}

Circle_2 get_circle() {
    const double square = 10.0;
    Circle_2 circle = Circle_2(Point_2(0,0), square);

    CGAL::Bbox_2 bounding = circle.bbox();
    std::cout << "Bounding:" << bounding << std::endl;

    return circle;
}


std::vector<Rect_2> get_obj(std::vector<Rect_2> in ,int n)
{
    for (int i = 0; i < n; ++i)
    {
        in.push_back(do_rmd_obj());
    }
    return in;
}

Point_2 get_rnmd_loc(){
    return Point_2(std::experimental::randint(0,30), std::experimental::randint(0,30));
}

bool isIntersected(Circle_2 placable_circle, std::vector<Rect_2> rects, std::vector<Circle_2> circles) {
    return false;
}

std::vector<Rect_2> adjustPosition(std::vector<Rect_2> rect_list) {
    //ToDo: change y Position, x Position is calc right
    for (Rect_2 rect : rect_list) {
        std::cout << "Curr:" << rect << std::endl;
        int new_x = std::experimental::randint(0,30);
        std::cout << new_x << std::endl;
        Rect_2 new_rect = Rect_2(Point_2(new_x - rect.xmax(), rect.ymin()), Point_2(new_x, rect.ymax()));
        std::cout << "New:" << new_rect << std::endl;
        rect = new_rect;
    }
    return rect_list;
}

int main()
{
    //Idea: Größe der Map, und dann Rects nochmal umändern von der def mit der größe der map und dann hinzufügen
    // Problem find a multidimensional datastructure which accept more than one datastructre
    // CGAL::Pointer_property_map<Point_2> prop_map {}; //do something there

    std::vector<Rect_2> outer_section_map = { Rect_2(Point_2(0,0), Point_2(-1, 10)),
                                          Rect_2(Point_2(0,10), Point_2(30, 11)),
                                          Rect_2(Point_2(30,0), Point_2(31, 10)),
                                          Rect_2(Point_2(0,0), Point_2(30, -1)) };

    std::vector<Point_2> map = { Point_2(0,0),
                                 Point_2(30,0),
                                 Point_2(30,10),
                                 Point_2(0,10) };



    std::vector<Rect_2> placable_obj {get_obj({}, 5)};


    // for (size_t i = 0; i < placable_obj.size(); ++i)
    // {

    //     std::cout << "obj[" << i << "] = " << placable_obj[i].size() << std::endl;
    //     std::vector<size_t> indices(placable_obj[i].size()), out;
    //     std::iota(indices.begin(), indices.end(), 0);
    //     CGAL::convex_hull_2(indices.begin(), indices.end(), std::back_inserter(out),
    //                         Convex_hull_traits_2(CGAL::make_property_map(placable_obj[i])));
    //     for (size_t p : out)
    //     {
    //         std::cout << "points[" << p << "] = " << placable_obj[i][p] << std::endl;
    //     }
    // }

    get_circle();
    std::vector<Rect_2> vec_re {};

    vec_re = get_obj(vec_re,4);
    std::cout << vec_re.size() << std::endl;
    for (auto& i : vec_re) {
        CGAL::Bbox_2 bbox = i.bbox();
        std::cout << "Rect Box: " << bbox << std::endl;
    }

    std::vector<Rect_2> rect_list = get_obj(rect_list, 4);
    for (auto& rect : rect_list) std::cout << rect << std::endl;
    
    adjustPosition(rect_list);
    for (auto& rect : rect_list) std::cout << rect << std::endl;

    
    return 0;
}

// https://doc.cgal.org/latest/Barycentric_coordinates_2/index.html