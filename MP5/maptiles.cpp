/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

Point<3> convertToLAB(HSLAPixel pixel) {
    Point<3> result(pixel.h/360, pixel.s, pixel.l);
    return result;
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
  int rows = theSource.getRows();
	int columns = theSource.getColumns();
	MosaicCanvas * result = new MosaicCanvas(rows, columns);
	vector <Point<3> > pixels;
	map <Point<3>, int> indexs;

  size_t i = 0;
	while(i < theTiles.size()){
		HSLAPixel p1 = theTiles[i].getAverageColor();
		double setPoint [3];
		setPoint [0]= p1.h/360;
		setPoint [1]= p1.s;
		setPoint [2]= p1.l;
		Point <3> temp(setPoint);
		pixels.push_back(temp);
    i++;
	}

  size_t j = 0;
	while(j < pixels.size()){
		indexs[pixels[j]] = j;
    j++;
	}

	KDTree <3> source(pixels);
	for(int row = 0; row < rows; row++){
		for(int col = 0; col < columns; col++){
			HSLAPixel p2 = theSource.getRegionColor(row, col);
			double pixelA [3];
			pixelA [0]= p2.h/360;
			pixelA [1]= p2.s;
			pixelA [2]= p2.l;
			Point <3> p3(pixelA);
			Point <3> Image = source.findNearestNeighbor(p3);
			int index = indexs[Image];
			TileImage* img = &theTiles[index];
			result->setTile(row, col, img);
		}
	}

return result;
}

TileImage* get_match_at_idx(const KDTree<3>& tree,
                                  map<Point<3>, int> tile_avg_map,
                                  vector<TileImage>& theTiles,
                                  const SourceImage& theSource, int row,
                                  int col)
{
    // Create a tile which accurately represents the source region we'll be
    // using
    HSLAPixel avg = theSource.getRegionColor(row, col);
    Point<3> avgPoint = convertToLAB(avg);
    Point<3> nearestPoint = tree.findNearestNeighbor(avgPoint);

    // Check to ensure the point exists in the map
    map< Point<3>, int >::iterator it = tile_avg_map.find(nearestPoint);
    if (it == tile_avg_map.end())
        cerr << "Didn't find " << avgPoint << " / " << nearestPoint << endl;

    // Find the index
    int index = tile_avg_map[nearestPoint];
    return &theTiles[index];

}
