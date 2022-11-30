
#include <blend2d.h>
#include "XYAxis.h"
#include "XYPlot.h"
#include "BLAlignedText.h"


#include <dash.h>

#include "XYPoint.h"

#include "XYBlend2dBackend.h"

/*
int main(int argc, char* argv[])
{
	std::vector<float> dash = { 20,6,1,6 };
	float dash_offset = 0.0;
	std::vector<float> xp;
	std::vector<float> yp;
	float r = 0;
	std::vector<float> pt_nodes_x;
	std::vector<float> pt_nodes_y;
	//for (int i = 0; i < 100; i += 1)
	//{
	//	pt_nodes_x.push_back (4 * i);
	//	pt_nodes_y.push_back(100 * sin(pt_nodes_x[i] / 30) + 300);
	//}
	pt_nodes_x.push_back(0);
	pt_nodes_y.push_back(0);
	pt_nodes_x.push_back(100);
	pt_nodes_y.push_back(100);

	makeDashedPolyline(pt_nodes_x,pt_nodes_y,dash,dash_offset,xp,yp,r);
	// отрисовка
	BLImage img(480, 480, BL_FORMAT_PRGB32);
	BLContext ctx(img);
	ctx.setFillStyle(BLRgba32(0xFF555555));
	ctx.setCompOp(BL_COMP_OP_SRC_COPY);
	ctx.fillAll();
	ctx.setStrokeStyle(BLRgba32(0xFFFFffff));
	ctx.setStrokeWidth(2);
	ctx.setFillStyle(BLRgba32(0xFF55ff55));
	
	for (int i = 0; i < xp.size() / 2; i++)
	{
		ctx.strokeLine(xp[2 * i], yp[2 * i], xp[2 * i + 1], yp[2 * i + 1]);
	}
	ctx.end();

	BLImageCodec codec;
	codec.findByName("PNG");
	img.writeToFile("result.png", codec);
	return 0;
}
*/
#include <blend2d.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
	XYBlend2dBackend be(600, 600);
	be.setFillColor4I(255, 20, 255, 255);

	std::vector<float> pattern = { 10,4 };
	be.setStrokePattern(pattern, 0);
	std::vector<float> px = { 100,130,200,240,400 };
	std::vector<float> py = { 40,60,200,100,400 };
	be.dashedPolyline(px, py);

	std::vector<unsigned int> colors =
	{ 0xffff0000,
	0xffffff00,
	0xffffffff,
	0xffff00ff,
	0xffff44ff,
	0xff00ff00,
	0xff00ffff,
	0xff0000ff,
	0xff55ff55,
	0xff0055ff,
	0xffff5555
	};

	std::vector < std::vector <float> > patttrns =
	{
		{2,2},
		{4,2},
		{6,2,6},
		{10,2,2,2},
		{30,5,5,5},
		{10,20,30},
		{20,20},
		{40,10,4,10,4,2},
		{40,20,40},
		{50}
	};

	XYData data;
	for (int i = 0; i < 10; ++i)
	{
		XYTrack track;
		track.color = colors[i%colors.size()];
		track.name = "track "+std::to_string(i+1);
		track.pathEffect = patttrns[i % patttrns.size()];;
		track.width = 3;
		for (float j = 0; j < 2.0 * M_PI; j+=0.06)
		{
			track.points.push_back(XYPoint(j, 100*sin(j+i)));
		}
		data.tracks.push_back(track);
	}

	be.translate(0, 0);
	be.scale(0.5, 0.5);
	plotMain(
		&be,
		600,
		600,
		"Title",
		"X",
		"Y",
		"fonts/OpenSans-Light.ttf",
		"fonts/OpenSans-Light.ttf",
		"fonts/OpenSans-Light.ttf",
		20,
		20,
		40,
		5,
		5,
		-3,
		-3,
		0xFF666666,
		0xffffffff,
		0xffffffff,
		0xffffffff,
		0xffffffff,
		// высота шрифта значений отсчетов на осях
		1,
		2,
		&data
	);
	be.scale(2, 2);
	be.translate(0, 0);
	
	
	
	
	be.translate(300, 0);
	be.scale(0.5, 0.5);
	plotMain(
		&be,
		600,
		600,
		"Title",
		"X",
		"Y",
		"fonts/OpenSans-Light.ttf",
		"fonts/OpenSans-Light.ttf",
		"fonts/OpenSans-Light.ttf",
		20,
		20,
		40,
		5,
		5,
		-1,
		-3,
		0xFF666666,
		0xffffffff,
		0xffffffff,
		0xffffffff,
		0xffffffff,
		// высота шрифта значений отсчетов на осях
		1,
		2,
		&data
	);
	be.scale(2, 2);
	be.translate(-300, 0);
	





	return 0;
}
