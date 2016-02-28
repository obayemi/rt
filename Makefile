NAME		= rt

SRC_NAMES	= main.cpp \
			  Ray.cpp \
			  Exceptions.cpp \
			  RotMatrix.cpp \
			  Intersection.cpp \
			  Color.cpp \
			  Scene.cpp \
			  Object.cpp \
			  Camera.cpp \
			  CameraRay.cpp \
			  Light.cpp \
			  Mesh.cpp \
			  Plane.cpp \
			  Sphere.cpp \
			  Solver1.cpp \
			  Solver2.cpp \
			  ColorTexture.cpp \
			  TypesInit.cpp \
			  Texture.cpp \
			  PointLight.cpp
SRC_NAMES	+= jsoncpp/jsoncpp.cpp

SRCDIR		= src/

SRC			= $(addprefix src/,$(SRC_NAMES))
OBJ			= $(SRC:.cpp=.o)


CXXFLAGS	= -W -Wall -Wextra -std=c++11
LDFLAGS		= -lsfml-graphics -lsfml-window -lsfml-system

ifeq ($(DEBUG),yes)
	CXXFLAGS	+= -g
else
	CXXFLAGS	+= -O2
endif

CXX			= clang++
LD			= clang++


$(NAME):	$(OBJ)
	@echo
	@echo '[LINKING]'
	$(LD) -o $@ $^ $(LDFLAGS)
	@echo
	@echo '[ $(NAME) build! ]'
	@echo

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS)

.PHONY: all doc clean mrproper return

all:		$(NAME)

doc:
	doxygen doxygen.config

clean:
	@echo [ CLEANING BUILD OBJECTS ]
	@rm -fv $(OBJ)
	@echo

fclean:		clean
	@echo [ REMOVING BINARIES ]
	@rm -fv $(NAME)
	@echo

cleandoc:
	@echo [ REMOVING DOCUMENTATION ]
	@rm -rf doc MO
	@echo

mrproper:	fclean cleandoc

re:			clean all

