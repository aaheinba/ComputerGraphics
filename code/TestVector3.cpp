/// \file TestVector3.cpp
/// \brief A collection of Catch2 unit tests for the Vector3 class.
/// \author Chad Hogg and Aaron Heinbaugh
/// \version A04

#include <sstream>

#include "Vector3.hpp"

#define CATCH_CONFIG_MAIN
#include <catch.hpp>


// Note: I included just a few representative / unusually tricky test cases here.  You should write the others, for every function declared in Vector3.hpp.

SCENARIO ("Vector3 constructors.", "[Vector3][A04]") {
  GIVEN ("Nothing at all.") {
    WHEN ("I use the default Vector3 constructor.") {
      Vector3 v;
      THEN ("All components should be 0.0f.") {
	REQUIRE (0.0f == Approx (v.m_x));
	REQUIRE (0.0f == Approx (v.m_y));
	REQUIRE (0.0f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 5.3f to the constructor with one parameter.") {
      Vector3 v (5.3f);
      THEN ("All components should be 5.3f.") {
	REQUIRE (5.3f == Approx (v.m_x));
	REQUIRE (5.3f == Approx (v.m_y));
	REQUIRE (5.3f == Approx (v.m_z));
      }
    }

    WHEN ("I pass 3.4f, 9.1f, and -2.4f to the constructor with three parameters.") {
      Vector3 v (3.4f, 9.1f, -2.4f);
      THEN ("The components should be 3.4f, 9.1f, and -2.4f respectively.") {
	REQUIRE (3.4f == Approx (v.m_x));
	REQUIRE (9.1f == Approx (v.m_y));
	REQUIRE (-2.4f == Approx (v.m_z));
      }
    }
  }
}


// ... lots of missing functions ...
SCENARIO ("Vector3 set.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and set them to 2.2.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    float f = 2.2f;
    WHEN ("I set each x, y, z of the vector to 2.2.") {
      v1.set (f);
      THEN ("The x, y, z of vector will all be 2.2.") {
	REQUIRE (2.2f == Approx (v1.m_x));
	REQUIRE (2.2f == Approx (v1.m_y));
	REQUIRE (2.2f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 set individual x,y,z.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and set them to 1.2, 2.3, 3.4.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    float f1 = 1.2f;
    float f2 = 2.3f;
    float f3 = 3.4f;
    WHEN ("I set each x, y, z of the vector to 1.2, 2.3, 3.4.") {
      v1.set (f1,f2,f3);
      THEN ("The x, y, z of vector will be  1.2, 2.3, 3.4.") {
	REQUIRE (1.2f == Approx (v1.m_x));
	REQUIRE (2.3f == Approx (v1.m_y));
	REQUIRE (3.4f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 negate.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and negate them to -1.1, -2.2, -3.3.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    WHEN ("I the vector is negated.") {
      v1.negate();
      THEN ("The x, y, z of vector will be  -1.1, -2.2, -3.3.") {
	REQUIRE (-1.1f == Approx (v1.m_x));
	REQUIRE (-2.2f == Approx (v1.m_y));
	REQUIRE (-3.3f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 dot product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the dot product of the vectors.") {
      float dot = v1.dot (v2);
      THEN ("The dot product should be the sum of the element-wise products.") {
	REQUIRE (22.11f == Approx (dot));
      }
    }
  }
}

SCENARIO ("Vector3 angle between.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the angle between the vectors.") {
      float angle = v1.angleBetween (v2);
      THEN ("The angle between should be the dot product divided by the product of the magnitudes of each vector.") {
	REQUIRE (0.86137f == Approx (angle));
      }
    }
  }
}

SCENARIO ("Vector3 cross product.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (0.1f, -2.0f, 8.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (0.1f, -2.0f, 8.0f);
    WHEN ("I find the cross product of the vectors.") {
      Vector3 v3 = v1.cross (v2);
      THEN ("The cross product should be the determinate of the i, j, k columns with alternating signs.") {
	REQUIRE (24.2f == Approx (v3.m_x));
  REQUIRE (-8.47f == Approx (v3.m_y));
  REQUIRE (-2.42f == Approx (v3.m_z));
      }
    }
  }
}

SCENARIO ("Vector3 length.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    WHEN ("I find the length the vector.") {
      float length = v1.length();
      THEN ("The length of the vector should be the square root of vector: x^2 + y^2 + z^2.") {
	REQUIRE (4.1158f == Approx (length));
      }
    }
  }
}

SCENARIO ("Vector3 normalize.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    WHEN ("I the vector is normalize.") {
      v1.normalize();
      THEN ("The the vector will be length one in the same direction") {
	REQUIRE (0.26726f == Approx (v1.m_x));
	REQUIRE (0.53452f == Approx (v1.m_y));
	REQUIRE (0.80178f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator+=.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (1.1f, 2.2f, 3.3f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (1.1f, 2.2f, 3.3f);
    WHEN ("I add the vectors to eachother.") {
      v1 += v2;
      THEN ("The the vectors' x,y,z's will be added together.") {
	REQUIRE (2.2f == Approx (v1.m_x));
	REQUIRE (4.4f == Approx (v1.m_y));
	REQUIRE (6.6f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator-=.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (1.1f, 2.2f, 3.3f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (1.1f, 2.2f, 3.3f);
    WHEN ("I subtract v2 from v1.") {
      v1 -= v2;
      THEN ("v1's x,y,z's will be v2's x,y,z less.") {
	REQUIRE (0.0f == Approx (v1.m_x));
	REQUIRE (0.0f == Approx (v1.m_y));
	REQUIRE (0.0f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator*=.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and a scaler 2.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    float s = 2.0f;
    WHEN ("I multiply the vector by 2.") {
      v1 *= s;
      THEN ("The vector's x,y,z will be multiplied by 2.") {
	REQUIRE (2.2f == Approx (v1.m_x));
	REQUIRE (4.4f == Approx (v1.m_y));
	REQUIRE (6.6f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator/=.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and a scaler 2.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    float s = 2.0f;
    WHEN ("I divide the vector by 2.") {
      v1 /= s;
      THEN ("The vector's x,y,z will be divided by 2.") {
	REQUIRE (0.55f == Approx (v1.m_x));
	REQUIRE (1.1f == Approx (v1.m_y));
	REQUIRE (1.65f == Approx (v1.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator+.", "[Vector3][A04]") {
  GIVEN ("Two vector initialized to (1.1f, 2.2f, 3.3f) and (1.0f, 1.0f, 1.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (1.0f, 1.0f, 1.0f);
    WHEN ("I add the vector together.") {
      Vector3 v3 = v1 + v2;
      THEN ("The resulting vector's x,y,z will be the sum of each vectors' x,y,z.") {
	REQUIRE (2.1f == Approx (v3.m_x));
	REQUIRE (3.2f == Approx (v3.m_y));
	REQUIRE (4.3f == Approx (v3.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator-.", "[Vector3][A04]") {
  GIVEN ("Two vectors initialized to (1.1f, 2.2f, 3.3f) and (1.0f, 1.0f, 1.0f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    Vector3 v2 (1.0f, 1.0f, 1.0f);
    WHEN ("I subtract the vectors.") {
      Vector3 v3 = v1 - v2;
      THEN ("The resulting vector's x,y,z will be the difference of each vectors' x,y,z.") {
	REQUIRE (0.1f == Approx (v3.m_x));
	REQUIRE (1.2f == Approx (v3.m_y));
	REQUIRE (2.3f == Approx (v3.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator- negate.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f).") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    WHEN ("I negate the vector.") {
      Vector3 v3 = -v1;
      THEN ("The resulting vector's x,y,z will be the negation of the vectors x,y,z.") {
	REQUIRE (-1.1f == Approx (v3.m_x));
	REQUIRE (-2.2f == Approx (v3.m_y));
	REQUIRE (-3.3f == Approx (v3.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator* scaler by vector.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and a float 2.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    float s = 2.0f;
    WHEN ("I multiply 2 by the vector.") {
      Vector3 v2 = s * v1;
      THEN ("The resulting vector's x,y,z will be multiplied by 2.") {
	REQUIRE (2.2f == Approx (v2.m_x));
	REQUIRE (4.4f == Approx (v2.m_y));
	REQUIRE (6.6f == Approx (v2.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator* vector by scaler.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and a float 2.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    float s = 2.0f;
    WHEN ("I multiply the vector by 2.") {
      Vector3 v2 = v1 * s;
      THEN ("The resulting vector's x,y,z will be multiplied by 2.") {
	REQUIRE (2.2f == Approx (v2.m_x));
	REQUIRE (4.4f == Approx (v2.m_y));
	REQUIRE (6.6f == Approx (v2.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 operator/ vector by scaler.", "[Vector3][A04]") {
  GIVEN ("A vector initialized to (1.1f, 2.2f, 3.3f) and a float 2.") {
    Vector3 v1 (1.1f, 2.2f, 3.3f);
    float s = 2.0f;
    WHEN ("I divide the vector by 2.") {
      Vector3 v2 = v1 / s;
      THEN ("The resulting vector's x,y,z will be divided by 2.") {
	REQUIRE (0.55f == Approx (v2.m_x));
	REQUIRE (1.1f == Approx (v2.m_y));
	REQUIRE (1.65f == Approx (v2.m_z));;
      }
    }
  }
}

SCENARIO ("Vector3 stream insertion.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (4.3, 102345, and -1.2).") {
    Vector3 v(4.3f, 102345.0f, -1.2f);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << v;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
	REQUIRE ("      4.30 102345.00     -1.20" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
	REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Vector3 equality.", "[Vector3][A04]") {
  GIVEN ("A vector initialized with (1.2, 3.4, and 0.1).") {
    Vector3 v1(1.2f, 3.4f, 0.1f);
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.1000000001).") {
      Vector3 v2(1.2f, 3.4f, 0.1000000001f);
      bool equal = v1 == v2;
      THEN ("They should be equal.") {
	REQUIRE (true == equal);
      }
    }
    WHEN ("I compare with a vector initialized with (1.2, 3.4, and 0.101).") {
      Vector3 v3(1.2f, 3.4f, 0.101f);
      bool equal = v1 == v3;
      THEN ("They should not be equal.") {
	REQUIRE (false == equal);
      }
    }
  }
}
