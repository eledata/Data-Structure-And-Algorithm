#ifndef _CPPCDS_TYPE_TRAIT_H_
#define _CPPCDS_TYPE_TRAIT_H_

namespace cppcds
{
	// ���������ǲ�ȡ��ͬ���Ե�__true_type��__false_type����
	struct _cppcds_true_type{
	};

	struct _cppcds_false_type{
	};

	template<class T>
	struct _cppcds_type_trait
	{
		typedef _cppcds_true_type		this_dummy_member_must_be_first; // ��֮һ�仰�ܽ�����Ķ���:�Ǿ��ǣ�__true_typeΪ�ػ�׼����.

		typedef _cppcds_false_type		has_trivial_default_constructor; // Ĭ�ϵĹ��캯��
		typedef _cppcds_false_type		has_trivial_copy_constructor;    // ���ƹ��캯��
		typedef _cppcds_false_type		has_trivial_assignment_operator; // ��ֵ����
		typedef _cppcds_false_type		has_trivial_destructor;          // ��������
		typedef _cppcds_false_type		is_POD_type;                     // ƽ������
	};

	template<> struct _cppcds_type_trait<bool>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<char>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<signed char>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<unsigned char>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<wchar_t>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<int>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<unsigned int>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<short>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<unsigned short>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<long>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<unsigned long>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<long long>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<unsigned long long>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<float>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<double>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};

	template<> struct _cppcds_type_trait<long double>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;                     
	};


	// һ����Ƶ����
	//template <class T>
	//struct _cppcds_type_trait
	//{
	//	typedef _cppcds_true_type		has_trivial_default_constructor; 
	//	typedef _cppcds_true_type		has_trivial_copy_constructor;    
	//	typedef _cppcds_true_type		has_trivial_assignment_operator; 
	//	typedef _cppcds_true_type		has_trivial_destructor;          
	//	typedef _cppcds_true_type		is_POD_type;    
	//};
	// ԭ��ָ�����ƫ�ػ�
	template <class T>
	struct _cppcds_type_trait<T*>
	{
		typedef _cppcds_true_type		has_trivial_default_constructor; 
		typedef _cppcds_true_type		has_trivial_copy_constructor;    
		typedef _cppcds_true_type		has_trivial_assignment_operator; 
		typedef _cppcds_true_type		has_trivial_destructor;          
		typedef _cppcds_true_type		is_POD_type;    
	};
	

	template <class T> struct _cppcds_is_integer
	{
		typedef _cppcds_false_type		_integer; 
	};

	template <> struct _cppcds_is_integer<bool>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<char>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<signed char>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<unsigned char>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<short>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<unsigned short>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<int>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<unsigned int>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<long>
	{
		typedef _cppcds_true_type		_integer; 
	};

	template <> struct _cppcds_is_integer<unsigned long>
	{
		typedef _cppcds_true_type		_integer; 
	};

}	// �����ռ��β

#endif
