include <MCAD/stepper.scad>

module motors(){
	for(r=[60,180,300]){
		rotate([90,90,r]){
			color([0.5,0.5,0.5])translate([-32,0,125])motor(model=Nema17);
		}
	}
}


module top_support(rod_rotation){
	color([0.4,0.4,0.7,0.5])linear_extrude(file = "parts.dxf", layer = "corner_rod_face",height =6,convexity = 10);

color([0.7,0.4,0.4])translate([0,0,-6])linear_extrude(file = "parts.dxf", layer = "corner_rod_support",height =6,convexity = 10);

	color([0.4,0.4,0.7,0.5])translate([0,0,58])linear_extrude(file = "parts.dxf", layer = "corner_blank_face",height =6,convexity = 10);

	rotate([90,0,30+180])translate([-46,6,-15])linear_extrude(file = "parts.dxf", layer = "top_front_support",height =6,convexity = 10);

	rotate([90,0,-30])translate([-46,6,9])linear_extrude(file = "parts.dxf", layer = "top_front_support",height =6,convexity = 10);

	rotate([90,0,-30])translate([-46,6,-17])linear_extrude(file = "parts.dxf", layer = "top_inner_support",height =6,convexity = 10);

	rotate([90,0,210])translate([-46,6,11])linear_extrude(file = "parts.dxf", layer = "top_inner_support",height =6,convexity = 10);

	rotate([90,0,0])translate([0,6,-26])linear_extrude(file = "parts.dxf", layer = "top_motor_support",height =6,convexity = 10);

	rotate([90,0,0])translate([0,6,-80])linear_extrude(file = "parts.dxf", layer = "top_rear_support",height =6,convexity = 10);
	


	color([0.7,0.4,0.4])rotate([90,0,120])translate([1,6,60])linear_extrude(file = "parts.dxf", layer = "top_rod_plate",height =6,convexity = 10);

	color([0.7,0.4,0.4])rotate([90,0,240])translate([-1,6,60])linear_extrude(file = "parts.dxf", layer = "top_rod_plate",height =6,convexity = 10);

	rotate([90,0,-120])translate([-1,48,66])rotate([0,0,-90+rod_rotation])rod_support();

	rotate([90,0,120])translate([1,48,66])rotate([0,0,90-rod_rotation])rod_support();
}


module bottom_support(rod_rotation){
	color([0.4,0.4,0.7,0.5])linear_extrude(file = "parts.dxf", layer = "corner_rod_face",height =6,convexity = 10);

color([0.7,0.4,0.4])translate([0,0,6])linear_extrude(file = "parts.dxf", layer = "corner_rod_support",height =6,convexity = 10);

	color([0.4,0.4,0.7,0.5])translate([0,0,-46])linear_extrude(file = "parts.dxf", layer = "corner_blank_face",height =6,convexity = 10);

	rotate([90,0,210])translate([-46,-40,-15])linear_extrude(file = "parts.dxf", layer = "base_front_support",height =6,convexity = 10);

	rotate([90,0,-30])translate([-46,-40,9])linear_extrude(file = "parts.dxf", layer = "base_front_support",height =6,convexity = 10);

	rotate([90,0,-30])translate([-46,-40,-17])linear_extrude(file = "parts.dxf", layer = "base_inner_support",height =6,convexity = 10);

	rotate([90,0,210])translate([-46,-40,11])linear_extrude(file = "parts.dxf", layer = "base_inner_support",height =6,convexity = 10);

	rotate([90,0,0])translate([0,-40,-26])linear_extrude(file = "parts.dxf", layer = "base_pulley_support",height =6,convexity = 10);

	rotate([90,0,0])translate([0,-40,-80])linear_extrude(file = "parts.dxf", layer = "base_rear_support",height =6,convexity = 10);



	color([0.7,0.4,0.4])rotate([90,0,300])translate([-1,-40,-66])linear_extrude(file = "parts.dxf", layer = "base_rod_plate",height =6,convexity = 10);
	color([0.7,0.4,0.4])rotate([90,0,-120])translate([-1,-40,60])linear_extrude(file = "parts.dxf", layer = "base_rod_plate",height =6,convexity = 10);

	rotate([90,0,-120])translate([-1,-10,66])rotate([0,0,90-rod_rotation])rod_support();

rotate([90,0,120])translate([1,-10,66])rotate([0,0,-90+rod_rotation])rod_support();

}


module top_supports(d,rod_rotation){
	for(r=[0,120,240]){
		rotate([0,0,r]){

			translate([0,d,0])top_support(rod_rotation);
		}
	}
}

module bottom_supports(d,rod_rotation){
	for(r=[0,120,240]){
		rotate([0,0,r]){
			translate([0,d,-394])bottom_support(rod_rotation);
		}
	}
}

module vertical_rods(d,l){
	for(r=[0,120,240]){
		rotate([0,0,r]){
			color([0.8,0.8,0.6])translate([25,d+25,-394])cylinder(h =l, r = 5, center = false);
			color([0.8,0.8,0.6])translate([-25,d+25,-394])cylinder(h =l, r = 5, center = false);
			color([0.4,0.4,0.3])translate([0,d+58,-394])cylinder(h =l, r = 3, center = false);
		}
	}
}

module linearBearings(d){
	for(r=[0,120,240]){
		rotate([0,0,r]){
			translate([25,d+25,-200])cylinder(h=29, r = 9.5, center = false);
			translate([-25,d+25,-200])cylinder(h=29, r = 9.5, center = false);
		}
	}
}



module supportRods(rod_rotation){
	for(r=[0,120,240]){
		rotate([0,0,r]){
			color([0.4,0.4,0.3])translate([-90,-127,-440])rotate([0,rod_rotation,0])cylinder(h=530, r = 3, center = false);
			color([0.4,0.4,0.3])translate([90,-127,-440])rotate([0,-rod_rotation,0])cylinder(h=530, r = 3, center = false);
			
			color([0.4,0.4,0.3])rotate([-90,0,90])translate([-95,-32,-125])cylinder(h=250, r = 3, center = false);

			color([0.4,0.4,0.3])rotate([-90,0,90])translate([-95,414,-125])cylinder(h=250, r = 3, center = false);
		}
	}
}



module carrige(){
	color([0.4,0.4,0.7,0.5])linear_extrude(file = "parts.dxf", layer = "carrige_body",height =6,convexity = 10);
	color([0.4,0.4,0.7,0.5])translate([0,0,23])linear_extrude(file = "parts.dxf", layer = "carrige_body",height=6,convexity = 10);

	rotate([0,90,180])translate([-14.5,-20,24])linear_extrude(file = "parts.dxf", layer = "carrige_side",height=6,convexity = 10);
	rotate([0,90,180])translate([-14.5,-20,-30])linear_extrude(file = "parts.dxf", layer = "carrige_side",height=6,convexity = 10);

rotate([90,0,0])translate([0,0,-46])linear_extrude(file = "parts.dxf", layer = "carrige_rear",height=6,convexity = 10);

}

module carriges(d){
	for(r=[0,120,240]){
		rotate([0,0,r]){
			translate([0,d,-200])carrige();
		}
	}
}


module rod_support(){
	translate([0,-13,0]){
		color([0.4,0.7,0.4])linear_extrude(file = "parts.dxf", layer = "rod_support_body_side",height=6,convexity = 10);
		color([0.4,0.7,0.4])translate([0,0,16])linear_extrude(file = "parts.dxf", layer = "rod_support_outer_side",height=6,convexity = 10);
		color([0.7,0.4,0.4])rotate([0,90,0])translate([-11,0,10])linear_extrude(file = "parts.dxf", layer = "rod_support_edge",height=6,convexity = 10);
		color([0.7,0.4,0.4])rotate([0,90,0])translate([-11,0,-16])linear_extrude(file = "parts.dxf", layer = "rod_support_edge",height=6,convexity = 10);
	}
}


module printHead(){
	linear_extrude(file = "parts.dxf", layer = "head",height=6,convexity = 10);
	translate([0,0,26])linear_extrude(file = "parts.dxf", layer = "head",height=6,convexity = 10);
	color([0.4,0.4,0.7,0.6])translate([0,0,32])linear_extrude(file = "parts.dxf", layer = "head_plate",height=6,convexity = 10);
	color([0.4,0.4,0.7,0.6])translate([0,0,-6])linear_extrude(file = "parts.dxf", layer = "head_plate",height=6,convexity = 10);


	for(r=[0,120,240]){
		color([0.7,0.7,0.4])rotate([90,0,30+r])translate([-35,6,24])linear_extrude(file = "parts.dxf", layer = "head_side",height=6,convexity = 10);
		color([0.7,0.7,0.4])rotate([90,0,30+r])translate([-35,6,-30])linear_extrude(file = "parts.dxf", layer = "head_side",height=6,convexity = 10);
	}
}


module printHead2(){
	linear_extrude(file = "parts.dxf", layer = "head",height=6,convexity = 10);
	//translate([0,0,26])linear_extrude(file = "parts.dxf", layer = "head",height=6,convexity = 10);
	//color([0.4,0.4,0.7,0.6])translate([0,0,32])linear_extrude(file = "parts.dxf", layer = "head_plate",height=6,convexity = 10);
	color([0.4,0.4,0.7,0.6])translate([0,0,-6])linear_extrude(file = "parts.dxf", layer = "head_plate",height=6,convexity = 10);


	for(r=[0,120,240]){
		color([0.7,0.7,0.4])rotate([90,0,30+r])translate([-28,3,24])linear_extrude(file = "parts.dxf", layer = "head_side_2",height=6,convexity = 10);
		color([0.7,0.7,0.4])rotate([90,0,30+r])translate([-28,3,-30])linear_extrude(file = "parts.dxf", layer = "head_side_2",height=6,convexity = 10);
	}
}


motors();
translate([0,0,-350])printHead2();

radius = 100;
rod_rotation = 21.4;

supportRods(rod_rotation);

linearBearings(radius);
vertical_rods(radius,400);
carriges(radius);
bottom_supports(radius,rod_rotation);
top_supports(radius,rod_rotation);