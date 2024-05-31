#include "bmp/bmp.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

PYBIND11_MODULE(vas_bmp, b) {
  pybind11::class_<vastina::bmp::bmp>(b, "bmp")
    .def(pybind11::init())
    .def_property("filename", &vastina::bmp::bmp::getfilename, &vastina::bmp::bmp::setfilename)
    .def_property("bgrdata", &vastina::bmp::bmp::getbgrdata, &vastina::bmp::bmp::setbgrdata)
    .def_property("line", &vastina::bmp::bmp::getline, &vastina::bmp::bmp::setline)
    .def_property("column", &vastina::bmp::bmp::getcolumn, &vastina::bmp::bmp::setcolumn)
    .def("resize", &vastina::bmp::bmp::resize)
    .def("write", &vastina::bmp::bmp::write)
    .def("setIndex", &vastina::bmp::bmp::setIndex);
  ;
}