#include <bits/stdc++.h>
using namespace std;

// ===============================================================
//                 BASIC CONSTANTS + CONVERSIONS
// ===============================================================

const double PI = acos(-1.0);

// ---------------- deg_to_rad ----------------
// Converts degrees → radians
// Use-case: CP problems giving angles in degrees.
double deg_to_rad(double d) { return d * PI / 180.0; }

// ---------------- rad_to_deg ----------------
// Converts radians → degrees
// Use-case: Output formatting when needed in degrees.
double rad_to_deg(double r) { return r * 180.0 / PI; }



// ===============================================================
//                      BASIC TRIG WRAPPERS
// ===============================================================

// ---------------- safe_acos(x) ----------------
// Clamps x inside [-1,1] before calling acos
// Necessary due to floating errors.
// Use-case: computing angles from dot products.
double safe_acos(double x) {
    if (x < -1) x = -1;
    if (x > 1) x =  1;
    return acos(x);
}

// ---------------- safe_asin(x) ----------------
// Same clamping for asin
double safe_asin(double x) {
    if (x < -1) x = -1;
    if (x > 1) x =  1;
    return asin(x);
}



// ===============================================================
//                 TRIANGLE: LAW OF COSINES
// ===============================================================

// ---------------- law_cos_side(a,b,C) ----------------
// Returns side c given: sides a,b and included angle C (in radians)
// Formula: c² = a² + b² - 2ab cos(C)
// Use-case:
//   - Missing 3rd side
//   - Triangle construction
double law_cos_side(double a, double b, double C) {
    return sqrt(a*a + b*b - 2*a*b*cos(C));
}

// ---------------- law_cos_angle(a,b,c) ----------------
// Returns: angle opposite side c (in radians)
// Formula: cost(A) = (b² + c² - a²) / (2bc)
// Use-case:
//   - Compute angles from 3 sides
//   - Safe against precision via safe_acos
double law_cos_angle(double a, double b, double c) {
    double x = (b*b + c*c - a*a) / (2*b*c);
    return safe_acos(x);
}



// ===============================================================
//                    TRIANGLE: LAW OF SINES
// ===============================================================

// ---------------- law_sines_angle(a,A,b) ----------------
// Given side a and angle A (radians), and side b,
// returns angle B using: a/sin(A) = b/sin(B)
// Use-case:
//   - Solve triangle when A + side ratios given.
double law_sines_angle(double a, double A, double b) {
    double val = b * sin(A) / a;
    return safe_asin(val);
}

// ---------------- law_sines_side(a,A,B) ----------------
// Given side a, angle A and angle B (in radians),
// returns side b using: a/sin(A) = b/sin(B)
double law_sines_side(double a, double A, double B) {
    return a * sin(B) / sin(A);
}



// ===============================================================
//                    TRIANGLE AREA FORMULAS
// ===============================================================

// ---------------- area_heron(a,b,c) ----------------
// Heron's formula.
// s = (a+b+c)/2 ; A = sqrt(s(s-a)(s-b)(s-c))
// Use-case:
//   - When you know all 3 sides.
double area_heron(double a, double b, double c) {
    double s = (a + b + c) / 2.0;
    return sqrt(max(0.0, s*(s-a)*(s-b)*(s-c))); // safe from negatives
}

// ---------------- area_2sides_angle(a,b,C) ----------------
// Area = 1/2 ab sin(C)
// Use-case:
//   - Two sides + included angle given.
double area_2sides_angle(double a, double b, double C) {
    return 0.5 * a * b * sin(C);
}

// ---------------- area_base_height(b,h) ----------------
// A = 1/2 base * height
// Use-case: direct geometry models
double area_base_height(double b, double h) {
    return 0.5 * b * h;
}



// ===============================================================
//                     TRIANGLE CENTERS
// ===============================================================

// ---------------- circumradius(a,b,c) ----------------
// Formula: R = a*b*c / (4 * area)
// Use-case:
//   - Circumcenter-related problems
//   - Useful for circle geometry
double circumradius(double a, double b, double c) {
    double A = area_heron(a,b,c);
    return (a*b*c) / (4*A);
}

// ---------------- inradius(a,b,c) ----------------
// r = A / s   (A = area, s = semiperimeter)
// Use-case:
//   - Incircle problems
//   - Distance to edges
double inradius(double a, double b, double c) {
    double s = (a+b+c)/2;
    double A = area_heron(a,b,c);
    return A / s;
}



// ===============================================================
//                         ANGLE TOOLS
// ===============================================================

// ---------------- angle_from_sides(a,b,c) ----------------
// Angle opposite side c (radians), using Law of Cosines.
// Same as law_cos_angle, provided for naming clarity.
// Use-case: computing triangle’s internal angles.
double angle_from_sides(double a, double b, double c) {
    return law_cos_angle(c, a, b);
}

// ---------------- normalize_angle(theta) ----------------
// Wrap angle into [0, 2π)
// Use-case:
//   - Rotations
//   - Ensuring consistent angle measurement
double normalize_angle(double t) {
    while (t < 0) t += 2*PI;
    while (t >= 2*PI) t -= 2*PI;
    return t;
}



// ===============================================================
//                      PROJECTIONS + DISTANCES
// ===============================================================

// ---------------- projection_length(a, theta) ----------------
// Projection of length “a” onto direction “theta” (radians).
// = a * cos(theta)
// Use-case:
//   - Physical problems
//   - Vector projection magnitude
double projection_length(double a, double theta) {
    return a * cos(theta);
}

// ---------------- height_from_side(a, A) ----------------
// Height from the side opposite angle A (in radians)
// h = a * sin(A)
// Use-case:
//   - Quick height computation in triangles
double height_from_side(double a, double A) {
    return a * sin(A);
}



// ===============================================================
//                     CIRCLES + ARCS + SECTORS
// ===============================================================

// ---------------- arc_length(r, theta) ----------------
// Arc length = r * θ (θ in radians)
// Use-case: circular motion, partial circumference
double arc_length(double r, double theta) {
    return r * theta;
}

// ---------------- sector_area(r, theta) ----------------
// Sector area = (1/2) r² * θ
double sector_area(double r, double theta) {
    return 0.5 * r * theta * r;
}

// ---------------- chord_length(r, theta) ----------------
// Chord length = 2r sin(θ/2)
double chord_length(double r, double theta) {
    return 2 * r * sin(theta/2);
}



// ===============================================================
//                       INVERSE TRIG HELPERS
// ===============================================================

// ---------------- angle_from_sin(x) ----------------
// Returns angle in radians for sin⁻¹(x)
double angle_from_sin(double x) { return safe_asin(x); }

// ---------------- angle_from_cos(x) ----------------
// Returns angle in radians for cos⁻¹(x)
double angle_from_cos(double x) { return safe_acos(x); }

// ---------------- angle_from_tan(x) ----------------
// tan⁻¹(x)
double angle_from_tan(double x) { return atan(x); }



// ===============================================================
//  NOTE: No main() — this is intended as a header-style .cpp file
// ===============================================================
int main() {
    cout << fixed << setprecision(6);

    // ===========================================================
    // 1. BASIC CONVERSIONS
    // ===========================================================
    cout << "\n=== BASIC ANGLE CONVERSIONS ===\n";
    cout << "90 degrees → radians = " << deg_to_rad(90) << "\n";
    cout << "PI/3 radians → degrees = " << rad_to_deg(PI/3) << "\n";


    // ===========================================================
    // 2. LAW OF COSINES
    // ===========================================================
    cout << "\n=== LAW OF COSINES ===\n";
    double c = law_cos_side(5, 7, deg_to_rad(60));
    cout << "Third side when a=5, b=7, C=60°: c = " << c << "\n";

    double A = law_cos_angle(3, 4, 5);
    cout << "Angle opposite side 3 in triangle (3,4,5): A = "
         << rad_to_deg(A) << "°\n";


    // ===========================================================
    // 3. LAW OF SINES
    // ===========================================================
    cout << "\n=== LAW OF SINES ===\n";
    double B = law_sines_angle(10, deg_to_rad(30), 12);
    cout << "Angle B from a=10, A=30°, b=12: "
         << rad_to_deg(B) << "°\n";

    double b_side = law_sines_side(10, deg_to_rad(30), deg_to_rad(45));
    cout << "Side b from a=10, A=30°, B=45°: b = " << b_side << "\n";


    // ===========================================================
    // 4. TRIANGLE AREA
    // ===========================================================
    cout << "\n=== TRIANGLE AREA ===\n";
    cout << "Heron area of (3,4,5): "
         << area_heron(3,4,5) << "\n";

    cout << "Area from two sides + angle (a=5, b=7, C=30°): "
         << area_2sides_angle(5,7,deg_to_rad(30)) << "\n";

    cout << "Area from base=10, height=6: "
         << area_base_height(10, 6) << "\n";


    // ===========================================================
    // 5. CIRCLE & TRIANGLE CENTERS
    // ===========================================================
    cout << "\n=== TRIANGLE CENTERS ===\n";
    cout << "Circumradius of (3,4,5): R = "
         << circumradius(3,4,5) << "\n";

    cout << "Inradius of (3,4,5): r = "
         << inradius(3,4,5) << "\n";


    // ===========================================================
    // 6. ANGLE FROM SIDES + NORMALIZATION
    // ===========================================================
    cout << "\n=== ANGLE TOOLS ===\n";
    double theta = angle_from_sides(4,5,6);
    cout << "Angle opposite side 6 in (4,5,6): "
         << rad_to_deg(theta) << "°\n";

    cout << "Normalize angle -1 rad → "
         << normalize_angle(-1) << "\n";


    // ===========================================================
    // 7. PROJECTIONS + HEIGHTS
    // ===========================================================
    cout << "\n=== PROJECTIONS ===\n";
    cout << "Projection of length 10 onto angle 30°: "
         << projection_length(10, deg_to_rad(30)) << "\n";

    cout << "Height from a=5 with angle=40°: "
         << height_from_side(5, deg_to_rad(40)) << "\n";


    // ===========================================================
    // 8. CIRCLE GEOMETRY
    // ===========================================================
    cout << "\n=== CIRCLE GEOMETRY ===\n";
    cout << "Arc length (r=10, θ=60°): "
         << arc_length(10, deg_to_rad(60)) << "\n";

    cout << "Sector area (r=10, θ=90°): "
         << sector_area(10, deg_to_rad(90)) << "\n";

    cout << "Chord length (r=10, θ=120°): "
         << chord_length(10, deg_to_rad(120)) << "\n";


    // ===========================================================
    // 9. INVERSE TRIG HELPERS
    // ===========================================================
    cout << "\n=== INVERSE TRIG ===\n";
    cout << "asin(0.5) = " << rad_to_deg(angle_from_sin(0.5)) << "°\n";
    cout << "acos(0.5) = " << rad_to_deg(angle_from_cos(0.5)) << "°\n";
    cout << "atan(1) = " << rad_to_deg(angle_from_tan(1)) << "°\n";


    cout << "\n=== DEMO COMPLETE ===\n";
    return 0;
}
