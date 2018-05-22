#ifndef FOR_EACH_H
#define FOR_EACH_H

#include <cgogn/core/basic/dart.h>
#include <cgogn/core/utils/type_traits.h>
#include <cgogn/core/cmap/map_base.h>

namespace cgogn {

struct for_each_traversal_tag {};

struct for_each_dart_traversal_tag : public for_each_traversal_tag {};

struct for_each_cell_traversal_tag : public for_each_traversal_tag {};


template <typename _Category>
struct traversal
{
	typedef _Category traversal_category;
	//ADD the cell type pointed
	//ADD Traversal Strategy
};

template <typename _Trav>
struct traversal_traits
{
<<<<<<< HEAD
	return typename traversal_traits<_Trav>::traversal_category;
}

template <typename _Trav>
struct traversal_traits<_Trav>
{
	typedef for_each_traversal_tag traversal_category;
=======
	typedef for_each_cell_traversal_tag traversal_category;
>>>>>>> be2106197ea75fcb1f79befc402de59d2b31c6e7
};

template <>
struct traversal_traits<Dart>
{
	typedef for_each_dart_traversal_tag traversal_category;
};

//template <typename FUNC>
//inline auto traversal_category()
//{
//	return typename traversal_traits<func_parameter_type<FUNC>>::traversal_category;
//}

/**
 * \brief apply a function on each dart of the map (including boundary darts)
 * if the function returns a boolean, the traversal stops when it first returns false
 * @tparam FUNC type of the callable
 * @param f a callable
 */
template <typename MAP, typename FUNC>
inline void for_each_helper(MAP& cmap, const FUNC& f, for_each_dart_traversal_tag)
{
	static_assert(is_func_parameter_same<FUNC, Dart>::value, "foreach_dart: given function should take a Dart as parameter");

	for (Dart it = cmap.all_begin(), last = cmap.all_end(); it != last; cmap.all_next(it))
	{
		if (!internal::void_to_true_binder(f, it))
			break;
	}
}

template <typename MAP, typename FUNC>
inline void for_each_helper(MAP& cmap, const FUNC& f, for_each_cell_traversal_tag)
{
	using CellType = func_parameter_type<FUNC>;

	cmap.template foreach_cell<TraversalStrategy::FORCE_DART_MARKING>(f, [] (CellType) { return true; });
}

template <typename MAP, typename FUNC>
inline void mfor_each(MAP& cmap, const FUNC& f)
{
	typename traversal_traits<func_parameter_type<FUNC>>::traversal_category category;
	for_each_helper(cmap, f, category);
}

}


#endif // FOR_EACH_H
