/*!
 * \file Exceptions.cpp
 * \author obayemi
 */

#include "Exceptions.hh"

char const * NotImplementedException::what() const throw() {
    return "Function not yet implemented.";
}
char const * RenderException::what() const throw() {
    return "somthing occured during render process";
}
char const * NotRendered::what() const throw() {
    return "Nop ;)";
}
char const * NoIntersect::what() const throw() {
    return "No Intersection found";
}
char const * InvalidScene::what() const throw() {
    return "Scene file invalid";
}
