/// \file TestMatrix3.cpp
/// \brief A collection of Catch2 unit tests for the Matrix3 class.
/// \author Aaron Heinbaugh
/// \version A05

#include <sstream>

#include "Matrix3.hpp"


#define CATCH_CONFIG_MAIN
#include <catch.hpp>

SCENARIO ("Matrix3 constuctor and data.", "[Matrix3][A05]") {
  GIVEN ("Nothing") {
    WHEN ("I construct the Matrix with 1,2,3,4,5,6,7,8,9 as params") {
      Matrix3 m1 (1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f );
      THEN ("The resulting Matrix rx,ry,rz,ux,uy,uz,bx,by,bz will be 1 to 9") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (2.0f == Approx (*(m1.data()+3)));
	REQUIRE (3.0f == Approx (*(m1.data()+6)));
    REQUIRE (4.0f == Approx (*(m1.data()+1)));
    REQUIRE (5.0f == Approx (*(m1.data()+4)));
    REQUIRE (6.0f == Approx (*(m1.data()+7)));
    REQUIRE (7.0f == Approx (*(m1.data()+2)));
    REQUIRE (8.0f == Approx (*(m1.data()+5)));
    REQUIRE (9.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("I construct the Matrix with default params") {
      Matrix3 m1;
      THEN ("The resulting Matrix will be identity") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (0.0f == Approx (*(m1.data()+3)));
	REQUIRE (0.0f == Approx (*(m1.data()+6)));
    REQUIRE (0.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (0.0f == Approx (*(m1.data()+7)));
    REQUIRE (0.0f == Approx (*(m1.data()+2)));
    REQUIRE (0.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("I construct the Matrix with 3 vectors (1,2,3)(4,5,6)(7,8,9) as params") {
      Matrix3 m1 (Vector3(1.0, 2.0, 3.0), Vector3(4.0, 5.0, 6.0), Vector3(7.0, 8.0, 9.0));
      THEN ("The resulting Matrix rx,ry,rz,ux,uy,uz,bx,by,bz will be 1 to 9") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (2.0f == Approx (*(m1.data()+3)));
	REQUIRE (3.0f == Approx (*(m1.data()+6)));
    REQUIRE (4.0f == Approx (*(m1.data()+1)));
    REQUIRE (5.0f == Approx (*(m1.data()+4)));
    REQUIRE (6.0f == Approx (*(m1.data()+7)));
    REQUIRE (7.0f == Approx (*(m1.data()+2)));
    REQUIRE (8.0f == Approx (*(m1.data()+5)));
    REQUIRE (9.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("I construct the Matrix with 3 vectors (1,2,3)(4,5,6)true as params") {
      Matrix3 m1 (Vector3(1.0, 2.0, 3.0), Vector3(4.0, 5.0, 6.0), true);
      THEN ("The resulting Matrix back will be normalize, right will be norm and perp to back and up, up with be norm and perp to back and right") {
	REQUIRE (-0.408248f == Approx (*m1.data()));
	REQUIRE (0.816497f == Approx (*(m1.data()+3)));
	REQUIRE (-0.408248f == Approx (*(m1.data()+6)));
    REQUIRE (-0.790912f == Approx (*(m1.data()+1)));
    REQUIRE (-0.093048 == Approx (*(m1.data()+4)));
    REQUIRE (.604815f == Approx (*(m1.data()+7)));
    REQUIRE (0.455842f == Approx (*(m1.data()+2)));
    REQUIRE (0.569803f == Approx (*(m1.data()+5)));
    REQUIRE (0.683763f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 setToIdentity.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setToIdentity") {
      m1.setToIdentity();
      THEN ("The resulting Matrix will be identity") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (.0f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 setToZero.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setToZero") {
      m1.setToZero();
      THEN ("The resulting Matrix will be all zeros") {
	REQUIRE (.0f == Approx (*m1.data()));
	REQUIRE (.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (.0f == Approx (*(m1.data()+4)));
    REQUIRE (.0f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 setRight.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setRight using Vector (2,2,2)") {
      m1.setRight(Vector3(2,2,2));
      THEN ("The resulting Matrix will be 2 in first col and 1 everywhere else") {
	REQUIRE (2.0f == Approx (*m1.data()));
	REQUIRE (2.0f == Approx (*(m1.data()+3)));
	REQUIRE (2.0f == Approx (*(m1.data()+6)));
    REQUIRE (1.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (1.0f == Approx (*(m1.data()+7)));
    REQUIRE (1.0f == Approx (*(m1.data()+2)));
    REQUIRE (1.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 getRight.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix has getRight called") {
      Vector3 v1 = m1.getRight();
      THEN ("The resulting Vector will be 1s everywhere ") {
	REQUIRE (1.0f == Approx (v1.m_x));
    REQUIRE (1.0f == Approx (v1.m_y));
    REQUIRE (1.0f == Approx (v1.m_z));
      }
    }
  }
}

SCENARIO ("Matrix3 setUp.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setUp using Vector (2,2,2)") {
      m1.setUp(Vector3(2,2,2));
      THEN ("The resulting Matrix will be 2 in 2nd col and 1 everywhere else") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (1.0f == Approx (*(m1.data()+3)));
	REQUIRE (1.0f == Approx (*(m1.data()+6)));
    REQUIRE (2.0f == Approx (*(m1.data()+1)));
    REQUIRE (2.0f == Approx (*(m1.data()+4)));
    REQUIRE (2.0f == Approx (*(m1.data()+7)));
    REQUIRE (1.0f == Approx (*(m1.data()+2)));
    REQUIRE (1.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 getUp.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix has getUp called") {
      Vector3 v1 = m1.getUp();
      THEN ("The resulting Vector will be 1s everywhere ") {
	REQUIRE (1.0f == Approx (v1.m_x));
    REQUIRE (1.0f == Approx (v1.m_y));
    REQUIRE (1.0f == Approx (v1.m_z));
      }
    }
  }
}

SCENARIO ("Matrix3 setBack.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setBack using Vector (2,2,2)") {
      m1.setBack(Vector3(2,2,2));
      THEN ("The resulting Matrix will be 2 in last col and 1 everywhere else") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (1.0f == Approx (*(m1.data()+3)));
	REQUIRE (1.0f == Approx (*(m1.data()+6)));
    REQUIRE (1.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (1.0f == Approx (*(m1.data()+7)));
    REQUIRE (2.0f == Approx (*(m1.data()+2)));
    REQUIRE (2.0f == Approx (*(m1.data()+5)));
    REQUIRE (2.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 getBack.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix has getBack called") {
      Vector3 v1 = m1.getBack();
      THEN ("The resulting Vector will be 1s everywhere ") {
	REQUIRE (1.0f == Approx (v1.m_x));
    REQUIRE (1.0f == Approx (v1.m_y));
    REQUIRE (1.0f == Approx (v1.m_z));
      }
    }
  }
}

SCENARIO ("Matrix3 setForward.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setForward using Vector (2,2,2)") {
      m1.setForward(Vector3(2,2,2));
      THEN ("The resulting Matrix will be -2 in last col and 1 everywhere else") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (1.0f == Approx (*(m1.data()+3)));
	REQUIRE (1.0f == Approx (*(m1.data()+6)));
    REQUIRE (1.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (1.0f == Approx (*(m1.data()+7)));
    REQUIRE (-2.0f == Approx (*(m1.data()+2)));
    REQUIRE (-2.0f == Approx (*(m1.data()+5)));
    REQUIRE (-2.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 getForward.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix has getForward called") {
      Vector3 v1 = m1.getForward();
      THEN ("The resulting Vector will be -1s everywhere ") {
	REQUIRE (-1.0f == Approx (v1.m_x));
    REQUIRE (-1.0f == Approx (v1.m_y));
    REQUIRE (-1.0f == Approx (v1.m_z));
      }
    }
  }
}

SCENARIO ("Matrix3 invertRotation() and transpose().", "[Matrix3][A05]") {
  GIVEN ("A matrix set from 1 to 9 ") {
      Matrix3 m1 (1,2,3,4,5,6,7,8,9);
    WHEN ("This matrix has invertRotation called") {
      m1.invertRotation();
      THEN ("The resulting Vector will be the transpose") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (4.0f == Approx (*(m1.data()+3)));
	REQUIRE (7.0f == Approx (*(m1.data()+6)));
    REQUIRE (2.0f == Approx (*(m1.data()+1)));
    REQUIRE (5.0f == Approx (*(m1.data()+4)));
    REQUIRE (8.0f == Approx (*(m1.data()+7)));
    REQUIRE (3.0f == Approx (*(m1.data()+2)));
    REQUIRE (6.0f == Approx (*(m1.data()+5)));
    REQUIRE (9.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 invert().", "[Matrix3][A05]") {
  GIVEN ("A matrix set from 1 to 9 ") {
      Matrix3 m1 (1,1,2,6,6,6,7,8,10);
    WHEN ("This matrix has invert called") {
      m1.invert();
      THEN ("The resulting Vector will be the invert matrix ") {
	REQUIRE (2.0f == Approx (*m1.data()));
	REQUIRE (1.0f == Approx (*(m1.data()+3)));
	REQUIRE (-1.0f == Approx (*(m1.data()+6)));
    REQUIRE (-3.0f == Approx (*(m1.data()+1)));
    REQUIRE ((-2.0/3.0f) == Approx (*(m1.data()+4)));
    REQUIRE (1.0f == Approx (*(m1.data()+7)));
    REQUIRE (1.0f == Approx (*(m1.data()+2)));
    REQUIRE ((-1.0/6.0f) == Approx (*(m1.data()+5)));
    REQUIRE (0.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 determinant().", "[Matrix3][A05]") {
  GIVEN ("A matrix set from 1 to 9 ") {
      Matrix3 m1 (1,1,2,6,6,6,7,8,10);
    WHEN ("This matrix has invert called") {
      float det = m1.determinant();
      THEN ("The result will be the determinant ") {
	REQUIRE (24.0f == Approx (det));
      }
    }
  }
}

SCENARIO ("Matrix3 setToScale.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setToScale using 2") {
      m1.setToScale(2);
      THEN ("The resulting Matrix will be 2 down diagonal and zeros everywhere else") {
	REQUIRE (2.0f == Approx (*m1.data()));
	REQUIRE (0.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (2.0f == Approx (*(m1.data()+4)));
    REQUIRE (.0f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (2.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("This matrix is setToScale using 2") {
      m1.setToScale(2,3,4);
      THEN ("The resulting Matrix will be 2,3,4 down diagonal and zeros everywhere else") {
	REQUIRE (2.0f == Approx (*m1.data()));
	REQUIRE (0.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (3.0f == Approx (*(m1.data()+4)));
    REQUIRE (.0f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (4.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 setToShear.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setToShearXByYz using (2,2)") {
      m1.setToShearXByYz(2.0,2.0);
      THEN ("The resulting Matrix will be 1s down diagonal, 2 up-x/back-x, and zeros else") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (0.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (2.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (.0f == Approx (*(m1.data()+7)));
    REQUIRE (2.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("This matrix is setToShearYByXz using (2,2)") {
      m1.setToShearYByXz(2.0,2.0);
      THEN ("The resulting Matrix will be 1s down diagonal, 2 right-y/back-y, and zeros else") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (2.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (.0f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (2.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("This matrix is setToShearZByXy using (2,2)") {
      m1.setToShearZByXy(2.0,2.0);
      THEN ("The resulting Matrix will be 1s down diagonal, 2 right-z/up-z, and zeros else") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (.0f == Approx (*(m1.data()+3)));
	REQUIRE (2.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.0f == Approx (*(m1.data()+4)));
    REQUIRE (2.0f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 setToRotation.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setToRotationX by 45 degrees") {
      m1.setToRotationX(45);
      THEN ("The resulting Matrix will rotate a vector around x-axis 45 degrees") {
	REQUIRE (1.0f == Approx (*m1.data()));
	REQUIRE (0.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (.707107f == Approx (*(m1.data()+4)));
    REQUIRE (.707107f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (-.707107f == Approx (*(m1.data()+5)));
    REQUIRE (.707107f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("This matrix is setToRotationY by 45 degrees") {
      m1.setToRotationY(45);
      THEN ("The resulting Matrix will rotate a vector around y-axis 45 degrees") {
	REQUIRE (.707107f == Approx (*m1.data()));
	REQUIRE (0.0f == Approx (*(m1.data()+3)));
	REQUIRE (-.707107f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (1.f == Approx (*(m1.data()+4)));
    REQUIRE (.0 == Approx (*(m1.data()+7)));
    REQUIRE (.707107f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (.707107f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("This matrix is setToRotationZ by 45 degrees") {
      m1.setToRotationZ(45);
      THEN ("The resulting Matrix will rotate a vector around z-axis 45 degrees") {
	REQUIRE (.707107f == Approx (*m1.data()));
	REQUIRE (.707107f  == Approx (*(m1.data()+3)));
	REQUIRE (0.0f == Approx (*(m1.data()+6)));
    REQUIRE (-.707107f  == Approx (*(m1.data()+1)));
    REQUIRE (.707107f == Approx (*(m1.data()+4)));
    REQUIRE (.0 == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (1.0f == Approx (*(m1.data()+8)));
      }
    }    
  }
}

SCENARIO ("Matrix3 setFromAngleAxis.", "[Matrix3][A05]") {
  GIVEN ("A matrix set to all ones") {
      Matrix3 m1 (1,1,1,1,1,1,1,1,1);
    WHEN ("This matrix is setFromAngleAxis by 45 degrees around Vector(1,1,1)") {
      m1.setFromAngleAxis(45, Vector3(1,1,1));
      THEN ("The resulting Matrix will rotate a vector around Vector(1,1,1) by 45 degrees") {
	REQUIRE (0.804738f == Approx (*m1.data()));
	REQUIRE (0.505879f == Approx (*(m1.data()+3)));
	REQUIRE (-0.310617f == Approx (*(m1.data()+6)));
    REQUIRE (-0.310617f == Approx (*(m1.data()+1)));
    REQUIRE (0.804738f == Approx (*(m1.data()+4)));
    REQUIRE (0.505879 == Approx (*(m1.data()+7)));
    REQUIRE (0.505879f == Approx (*(m1.data()+2)));
    REQUIRE (-0.310617 == Approx (*(m1.data()+5)));
    REQUIRE (0.804738 == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 negate().", "[Matrix3][A05]") {
  GIVEN ("A matrix set from 1 to 9 ") {
      Matrix3 m1 (1,2,3,4,5,6,7,8,9);
    WHEN ("This matrix has negate called") {
      m1.negate();
      THEN ("The resulting Vector will be the negated") {
	REQUIRE (-1.0f == Approx (*m1.data()));
	REQUIRE (-2.0f == Approx (*(m1.data()+3)));
	REQUIRE (-3.0f == Approx (*(m1.data()+6)));
    REQUIRE (-4.0f == Approx (*(m1.data()+1)));
    REQUIRE (-5.0f == Approx (*(m1.data()+4)));
    REQUIRE (-6.0f == Approx (*(m1.data()+7)));
    REQUIRE (-7.0f == Approx (*(m1.data()+2)));
    REQUIRE (-8.0f == Approx (*(m1.data()+5)));
    REQUIRE (-9.0f == Approx (*(m1.data()+8)));
      }
    }
  }
}

SCENARIO ("Matrix3 transform().", "[Matrix3][A05]") {
  GIVEN ("A matrix set from 1 to 9 ") {
      Matrix3 m1 (1,2,3,4,5,6,7,8,9);
    WHEN ("This matrix has transform called with vector(1,2,3)") {
      Vector3 v1 = m1.transform(Vector3(1,2,3));
      THEN ("The resulting Vector will be the negated") {
	REQUIRE (30.0f == Approx (v1.m_x));
	REQUIRE (36.0f == Approx (v1.m_y));
	REQUIRE (42.0f == Approx (v1.m_z));
      }
    }
  }
}

SCENARIO ("Matrix3 operators.", "[Matrix3][A05]") {
  GIVEN ("2 matrices set from 1 to 9, a scaler 2, a vector(1,2,3) ") {
      Matrix3 m1 (1,2,3,4,5,6,7,8,9);
      Matrix3 m2 (1,2,3,4,5,6,7,8,9);
      float scaler = 2;
      Vector3 v1 (1,2,3);
    WHEN ("Matrix 1 += 2") {
      m1+=m2;
      THEN ("The resulting Matrix will be the result of matrix addition") {
	REQUIRE (2.0f == Approx (*m1.data()));
	REQUIRE (4.0f == Approx (*(m1.data()+3)));
	REQUIRE (6.0f == Approx (*(m1.data()+6)));
    REQUIRE (8.0f == Approx (*(m1.data()+1)));
    REQUIRE (10.0f == Approx (*(m1.data()+4)));
    REQUIRE (12.0f == Approx (*(m1.data()+7)));
    REQUIRE (14.0f == Approx (*(m1.data()+2)));
    REQUIRE (16.0f == Approx (*(m1.data()+5)));
    REQUIRE (18.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("Matrix 1 -= 2") {
      m1-=m2;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (.0f == Approx (*m1.data()));
	REQUIRE (.0f == Approx (*(m1.data()+3)));
	REQUIRE (.0f == Approx (*(m1.data()+6)));
    REQUIRE (.0f == Approx (*(m1.data()+1)));
    REQUIRE (0.0f == Approx (*(m1.data()+4)));
    REQUIRE (.0f == Approx (*(m1.data()+7)));
    REQUIRE (.0f == Approx (*(m1.data()+2)));
    REQUIRE (.0f == Approx (*(m1.data()+5)));
    REQUIRE (.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("Matrix 1 *= scaler 2") {
      m1*2;
      THEN ("The resulting Matrix will be the result of matrix addition") {
	REQUIRE (2.0f == Approx (*m1.data()));
	REQUIRE (4.0f == Approx (*(m1.data()+3)));
	REQUIRE (6.0f == Approx (*(m1.data()+6)));
    REQUIRE (8.0f == Approx (*(m1.data()+1)));
    REQUIRE (10.0f == Approx (*(m1.data()+4)));
    REQUIRE (12.0f == Approx (*(m1.data()+7)));
    REQUIRE (14.0f == Approx (*(m1.data()+2)));
    REQUIRE (16.0f == Approx (*(m1.data()+5)));
    REQUIRE (18.0f == Approx (*(m1.data()+8)));
      }
    }

    WHEN ("Matrix 1 *= 2") {
      m1*=m2;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (30.0f == Approx (*m1.data()));
	REQUIRE (36.0f == Approx (*(m1.data()+3)));
	REQUIRE (42.0f == Approx (*(m1.data()+6)));
    REQUIRE (66.0f == Approx (*(m1.data()+1)));
    REQUIRE (81.0f == Approx (*(m1.data()+4)));
    REQUIRE (96.0f == Approx (*(m1.data()+7)));
    REQUIRE (102.0f == Approx (*(m1.data()+2)));
    REQUIRE (126.0f == Approx (*(m1.data()+5)));
    REQUIRE (150.0f == Approx (*(m1.data()+8)));
      }
    }
    
    WHEN ("Matrix 1 + 2") {
      Matrix3 m3 = m1+m2;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (2.0f == Approx (*m3.data()));
	REQUIRE (4.0f == Approx (*(m3.data()+3)));
	REQUIRE (6.0f == Approx (*(m3.data()+6)));
    REQUIRE (8.0f == Approx (*(m3.data()+1)));
    REQUIRE (10.0f == Approx (*(m3.data()+4)));
    REQUIRE (12.0f == Approx (*(m3.data()+7)));
    REQUIRE (14.0f == Approx (*(m3.data()+2)));
    REQUIRE (16.0f == Approx (*(m3.data()+5)));
    REQUIRE (18.0f == Approx (*(m3.data()+8)));
      }
    }

    WHEN ("Matrix 1 - 2") {
      Matrix3 m3 = m1-m2;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (.0f == Approx (*m3.data()));
	REQUIRE (.0f == Approx (*(m3.data()+3)));
	REQUIRE (.0f == Approx (*(m3.data()+6)));
    REQUIRE (.0f == Approx (*(m3.data()+1)));
    REQUIRE (.0f == Approx (*(m3.data()+4)));
    REQUIRE (.0f == Approx (*(m3.data()+7)));
    REQUIRE (.0f == Approx (*(m3.data()+2)));
    REQUIRE (.0f == Approx (*(m3.data()+5)));
    REQUIRE (.0f == Approx (*(m3.data()+8)));
      }
    }

    WHEN ("Matrix 1 * scaler 2") {
      Matrix3 m3 = m1*2;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (2.0f == Approx (*m3.data()));
	REQUIRE (4.0f == Approx (*(m3.data()+3)));
	REQUIRE (6.0f == Approx (*(m3.data()+6)));
    REQUIRE (8.0f == Approx (*(m3.data()+1)));
    REQUIRE (10.0f == Approx (*(m3.data()+4)));
    REQUIRE (12.0f == Approx (*(m3.data()+7)));
    REQUIRE (14.0f == Approx (*(m3.data()+2)));
    REQUIRE (16.0f == Approx (*(m3.data()+5)));
    REQUIRE (18.0f == Approx (*(m3.data()+8)));
      }
    }

    WHEN (" scaler 2 * Matrix 1") {
      Matrix3 m3 = 2*m1;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (2.0f == Approx (*m3.data()));
	REQUIRE (4.0f == Approx (*(m3.data()+3)));
	REQUIRE (6.0f == Approx (*(m3.data()+6)));
    REQUIRE (8.0f == Approx (*(m3.data()+1)));
    REQUIRE (10.0f == Approx (*(m3.data()+4)));
    REQUIRE (12.0f == Approx (*(m3.data()+7)));
    REQUIRE (14.0f == Approx (*(m3.data()+2)));
    REQUIRE (16.0f == Approx (*(m3.data()+5)));
    REQUIRE (18.0f == Approx (*(m3.data()+8)));
      }
    }

    WHEN (" Matrix 2 * Matrix 1") {
      Matrix3 m3 = m2*m1;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (30.0f == Approx (*m3.data()));
	REQUIRE (36.0f == Approx (*(m3.data()+3)));
	REQUIRE (42.0f == Approx (*(m3.data()+6)));
    REQUIRE (66.0f == Approx (*(m3.data()+1)));
    REQUIRE (81.0f == Approx (*(m3.data()+4)));
    REQUIRE (96.0f == Approx (*(m3.data()+7)));
    REQUIRE (102.0f == Approx (*(m3.data()+2)));
    REQUIRE (126.0f == Approx (*(m3.data()+5)));
    REQUIRE (150.0f == Approx (*(m3.data()+8)));
      }
    }

    WHEN (" Matrix 2 * vector") {
      Vector3 v2= m2*v1;
      THEN ("The resulting Matrix will be the result of matrix subtraction") {
	REQUIRE (30.0f == Approx (v2.m_x));
    REQUIRE (36.0f == Approx (v2.m_y));
    REQUIRE (42.0f == Approx (v2.m_z));
      }
    }    
  }
}

SCENARIO ("Matrix3 stream insertion.", "[Matrix3][A05]") {
  GIVEN ("A matrix initialized with (1,2,3,4,5,6,7,8,9).") {
    Matrix3 m1 (1,2,3,4,5,6,7,8,9);
    WHEN ("I insert it into an output stream.") {
      std::stringstream out;
      std::ostream& r = out << m1;
      THEN ("It should have included each component with a precision of 2 and field width of 10.") {
	REQUIRE ("      1.00      4.00      7.00\n      2.00      5.00      8.00\n      3.00      6.00      9.00\n" == out.str ());
      }
      THEN ("The original stream should have been returned.") {
	REQUIRE (&out == &r);
      }
    }
  }
}

SCENARIO ("Matrix3 equality.", "[Matrix3][A05]") {
  GIVEN ("A matrix initialized with (1,2,3,4,5,6,7,8,9).") {
    Matrix3 m1 (1,2,3,4,5,6,7,8,9);
    WHEN ("I compare with a A matrix initialized with (1,2,3,4,5,6,7,8,9.000000000001).") {
      Matrix3 m2 (1,2,3,4,5,6,7,8,9.000000000001);
      bool equal = m1 == m2;
      THEN ("They should be equal.") {
	REQUIRE (true == equal);
      }
    }
    WHEN ("I compare with a vector initialized with (1,2,3,4,5,6,7,8,9.001).") {
      Matrix3 m3 (1,2,3,4,5,6,7,8,9.001);
      bool equal = m1 == m3;
      THEN ("They should not be equal.") {
	REQUIRE (false == equal);
      }
    }
  }
}