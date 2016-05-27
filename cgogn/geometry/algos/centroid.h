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

#ifndef CGOGN_GEOMETRY_ALGOS_CENTROID_H_
#define CGOGN_GEOMETRY_ALGOS_CENTROID_H_

#include <cgogn/geometry/types/geometry_traits.h>
#include <cgogn/core/basic/cell.h>
#include <cgogn/core/utils/masks.h>

namespace cgogn
{

namespace geometry
{

template <typename VEC, typename CellType, typename MAP>
inline VEC centroid(
	const MAP& map,
	const CellType c,
	const typename MAP::template VertexAttribute<VEC>& attribute
)
{
	VEC result;
	set_zero(result);
	uint32 count = 0;
	map.foreach_incident_vertex(c, [&] (typename MAP::Vertex v)
	{
		result += attribute[v];
		++count;
	});
	result /= typename vector_traits<VEC>::Scalar(count);
	return result;
}

template <typename VEC, typename CellType, typename MAP, typename MASK>
inline void centroid(
	const MAP& map,
	const MASK& mask,
	const typename MAP::template VertexAttribute<VEC>& attribute,
	typename MAP::template Attribute<VEC, CellType::ORBIT>& cell_centroid
)
{
	map.foreach_cell([&] (CellType c)
	{
		cell_centroid[c] = centroid<VEC>(map, c, attribute);
	},
	mask);
}

template <typename VEC, typename CellType, typename MAP>
inline void centroid(
	const MAP& map,
	const typename MAP::template VertexAttribute<VEC>& attribute,
	typename MAP::template Attribute<VEC, CellType::ORBIT>& cell_centroid
)
{
	centroid<VEC, CellType>(map, CellFilters(), attribute, cell_centroid);
}

} // namespace geometry

} // namespace cgogn

#endif // CGOGN_GEOMETRY_ALGOS_CENTROID_H_
