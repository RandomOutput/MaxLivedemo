#include <sifteo.h>
#include "assets.gen.h"
using namespace Sifteo;

#define CUBE_CAPACITY 3

static AssetSlot MainSlot = AssetSlot::allocate()
    .bootstrap(BootstrapGroup);

static Metadata M = Metadata()
    .title("HELLO, WERLD!")
    .package("com.sifteo.hey.baby", "0.666")
    .icon(Icon)
    .cubeRange(CUBE_CAPACITY);

VideoBuffer video[CUBE_CAPACITY];
CubeSet isBizarro;

void main() {
	AudioTracker::play(RADMUSIC);
	
	System::paint();
	System::finish();
	for(CubeID cid : CubeSet::connected()) {
		video[cid].initMode(BG0_SPR_BG1);
		video[cid].bg0.image(vec(0,0), SuperSmiley);
		auto& spr = video[cid].sprites;
		spr[0].setImage(Star);
		spr[0].move(vec(64,32) - Star.pixelSize()/2);
		spr[1].setImage(WhiteDot);
		spr[1].move(vec(31, 67) - WhiteDot.pixelSize()/2);
		spr[2].setImage(WhiteDot);
		spr[2].move(vec(105, 63) - WhiteDot.pixelSize()/2);
		spr[3].setImage(BlackDot);
		spr[3].move(vec(31, 67) - BlackDot.pixelSize()/2);
		spr[4].setImage(BlackDot);
		spr[4].move(vec(105, 63) - BlackDot.pixelSize()/2);
		video[cid].attach(cid);
	}
	while(1) {
		for(CubeID cid : CubeSet::connected()) {
			auto accel = cid.accel().xy();
			//video[cid].sprites[0].move(vec(64,64) - Star.pixelSize()/2 + accel);
			auto& spr = video[cid].sprites;
			auto seconds = SystemTime::now().uptime();
			auto offset = vec(12 * sin(seconds * 2.f * M_PI), 0.f);
			spr[0].move(vec(64,32) - Star.pixelSize()/2 + offset);
			static const int frames[] = { 0, 1, 2, 3, 4, 3, 2, 1 };
			int frame = frames[SystemTime::now().cycleFrame(0.2f, arraysize(frames))];
			spr[0].setImage(Star, frame);
			spr[1].move(vec(31, 67) - WhiteDot.pixelSize()/2 + accel/4);
			spr[2].move(vec(105, 63) - WhiteDot.pixelSize()/2 - accel/4);
			
			auto nhood = video[cid].physicalNeighbors();
			if (
				nhood.hasCubeAt(TOP) || 
				nhood.hasCubeAt(LEFT) || 
				nhood.hasCubeAt(BOTTOM) || 
				nhood.hasCubeAt(RIGHT)
			) {
				if (!isBizarro.test(cid)) {
					video[cid].bg0.image(vec(0,0), BizarroSmiley);					
					isBizarro.mark(cid);
					AudioChannel(0).play(FOOSFX);
				}

			} else {
				if (isBizarro.test(cid)) {
					video[cid].bg0.image(vec(0,0), SuperSmiley);
					isBizarro.clear(cid);
					AudioChannel(1).play(FOOSFX);
				}
			}
		}
		System::paint();
	}
	
}