/**
 * @Author: Alexandre Biguet <alexandrebiguet>
 * @Date:   19 - May - 2018
 * @Last modified by:   alexandrebiguet
 * @Last modified time: 13 - Jun - 2018
 */

/**
 * Goal : testing the num_segment and for_each_segment algo
 *  - on linestrings
 *  - on rings
 */

#include <iostream>
#include <vector>

#include "Definitions.hpp"

template <typename Segment>
struct SegmentSaver {
  std::vector<Segment> _sides;

  inline void operator()(Segment const& s) { _sides.push_back(s); }
};

int main() {
  // LineString
  {
    std::cout << "\nLineString \n";

    BoostLineString2D line{{0, 0}, {1, 1}, {2, 2}, {3, 3}};

    if (bg::num_segments(line) != 3) {
      std::cout << "Error : Number of segment should be 3\n";
    } else {
      std::cout << "num segment : ok \n";
    }

    SegmentSaver<bg::model::referring_segment<BoostPoint2D>> segmentSaver;
    segmentSaver = bg::for_each_segment(line, segmentSaver);

    if (segmentSaver._sides.size() != 3) {
      std::cout << "Error : segment saver number of side should be 3 \n";
    } else {
      std::cout << "Segment Saver : ok \n";
    }
  }

  // Ring
  {
    std::cout << "\nRing \n";

    BoostRing2D ring{{0, 0}, {0, 1}, {1, 1}, {0, 0}};

    if (bg::num_segments(ring) != 3) {
      std::cout << "Error : Number of segment should be 3 \n";
    } else {
      std::cout << "num segment : ok \n";
    }

    SegmentSaver<bg::model::referring_segment<BoostPoint2D>> segmentSaver;
    segmentSaver = bg::for_each_segment(ring, segmentSaver);

    if (segmentSaver._sides.size() != 3) {
      std::cout << "Error : segment saver number of side should be 3 \n";
    } else {
      std::cout << "Segment Saver : ok \n";
    }
  }

  return 0;
}

// NumSegment.cpp ends here
