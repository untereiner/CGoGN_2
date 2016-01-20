/*******************************************************************************
* CGoGN: Combinatorial and Geometric modeling with Generic N-dimensional Maps  *
* Copyright (C) 2015, IGG Group, ICube, University of Strasbourg, France       *
*                                                                              *
* This library is free software; you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published by the *
* Free Software Foundation; either version 2.1 of the License, or (at your     *
* option) any later version.                                                   *
*                                                                              *
* This library is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
* for more details.                                                            *
*                                                                              *
* You should have received a copy of the GNU Lesser General Public License     *
* along with this library; if not, write to the Free Software Foundation,      *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
*                                                                              *
* Web site: http://cgogn.unistra.fr/                                           *
* Contact information: cgogn@unistra.fr                                        *
*                                                                              *
*******************************************************************************/

#ifndef GEOMETRY_ORIENTATION_H_
#define GEOMETRY_ORIENTATION_H_

#include <geometry/plane_3d.h>

namespace cgogn
{

namespace geometry
{
/**
 * return the orientation of point P w.r.t. the plane defined by 3 points
 * @param P the point
 * @param A plane point 1
 * @param B plane point 2
 * @param C plane point 3
 * @return the orientation
 */
template <typename VEC3_T>
Orientation3D testOrientation3D(const VEC3_T& P, const VEC3_T& A, const VEC3_T& B, const VEC3_T& C)
{
	static_assert(vector_traits<VEC3_T>::SIZE == 3ul, "The size of the vector must be equal to 3.");
	return Plane3D<VEC3_T>(A,B,C).orient(P);
}

/**
 * return the orientation of point P w.r.t. the plane defined by its normal and 1 point
 * @param P the point
 * @param N plane normal
 * @param PP plane point
 * @return the orientation
 */
template <typename VEC3_T>
Orientation3D testOrientation3D(const VEC3_T& P, const VEC3_T& N, const VEC3_T& PP)
{
	static_assert(vector_traits<VEC3_T>::SIZE == 3ul, "The size of the vector must be equal to 3.");
	return Plane3D<VEC3_T>(N, PP).orient(P) ;
}

} // namespace geometry
} // namespace cgogn

#endif // GEOMETRY_ORIENTATION_H_
