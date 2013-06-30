include <MCAD/bearing.scad>
include <MCAD/stepper.scad>


//overide the included bearing function to add our own 626 bearing size
function bearingDimensions(model) =
  model == 608 ? [8*mm, 22*mm, 7*mm]:
  model == 623 ? [3*mm, 10*mm, 4*mm]:
  model == 624 ? [4*mm, 13*mm, 5*mm]:
  model == 627 ? [7*mm, 22*mm, 7*mm]:
  model == 688 ? [8*mm, 16*mm, 4*mm]:
  model == 698 ? [8*mm, 19*mm, 6*mm]:
  model == 626 ? [6*mm, 19*mm, 6*mm]:
  [8*mm, 22*mm, 7*mm];


module bolts(){
	translate([0,0,-50])cylinder(h = 75, r=3, center = false, $fn=100);
	translate([0,0,-23])cylinder(h = 6, r=6, center = false, $fn=100);

	translate([-17,0,-35])cylinder(h = 30, r=3, center = false, $fn=100);
	rotate([0,90,0])translate([25,15,-38])cylinder(h = 60, r=3, center = false, $fn=10);
	rotate([0,90,0])translate([25,-15,-38])cylinder(h = 60, r=3, center = false, $fn=10);
}

color([0.4,0.4,0.4])bolts();



translate([45,0,1])rotate([0,180,0])color([0.6,0.6,0.6])motor(model=Nema17);

body();
translate([0,0,0])bearing(model=626);
translate([0,0,-46])bearing(model=626);
translate([0,0,0])clamp();



module clamp(){
	color([0.6,0.4,0.6])rotate([0,90,0])translate([20,0,-33])linear_extrude(file = "extruder.dxf", layer = "clamp_base",height =6,convexity = 10);
	
	translate([-27,0,-30])linear_extrude(file = "extruder.dxf", layer = "clamp_side",height =6,convexity = 10);
	
	translate([-27,0,-16])linear_extrude(file = "extruder.dxf", layer = "clamp_side",height =6,convexity = 10);
	
	translate([-17,0,-23])bearing(model=626);	
}



/*
module bolt(radius,length,head_radius){
	cylinder (h = radius, r=head_radius, center = true, $fn=6);
	cylinder (h = length, r=radius, center = false, $fn=10);
}

module nut(hole_radius, head_radius){
	difference(){
		cylinder (h = hole_radius, r=head_radius, center = true, $fn=6);
		cylinder (h = hole_radius, r=hole_radius, center = true, $fn=6);
	}
}
*/


module bearing_old(){
	color([0.5,0.5,0.5])difference(){
		cylinder (h = 6, r=9.5, center = true, $fn=100);
		cylinder (h = 7, r=7.5, center = true, $fn=100);
	}

	color([0.5,0.5,0.5])difference(){
		cylinder (h = 6, r=5, center = true, $fn=100);
		cylinder (h = 7, r=3, center = true, $fn=100);
	}

	color([0.4,0.4,0.4])for ( i = [0 : 8] )
	{
    	rotate( i * 360 / 9, [0, 0, 1])
    	translate([0, 6, 0])
    	sphere(r = 2,$fn=30);
	}

}

module body(){
	linear_extrude(file = "extruder.dxf", layer = "face_plate",height =6,convexity = 10);
	translate([0,0,-46])linear_extrude(file = "extruder.dxf", layer = "rear_plate",height =6,convexity = 10);

	color([0.6,0.4,0.6])rotate([0,90,0])translate([20,0,11])linear_extrude(file = "extruder.dxf", layer = "bolt_rear_support",height =6,convexity = 10);

	color([0.6,0.4,0.6])rotate([0,90,0])translate([20,0,-17])linear_extrude(file = "extruder.dxf", layer = "bolt_front_support",height =6,convexity = 10);

	color([0.4,0.6,0.6])rotate([0,90,90])translate([20,0,-25])linear_extrude(file = "extruder.dxf", layer = "side_plate",height =6,convexity = 10);

	color([0.4,0.6,0.6])rotate([0,90,90])translate([20,0,19])linear_extrude(file = "extruder.dxf", layer = "side_plate",height =6,convexity = 10);

	color([0.6,0.6,0.4])translate([0,0,12])linear_extrude(file = "extruder.dxf", layer = "59_teeth",height =6,convexity = 10);

	color([0.6,0.4,0.6])translate([0,0,12])linear_extrude(file = "extruder.dxf", layer = "11_teeth",height =6,convexity = 10);
}