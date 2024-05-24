#pragma once
#ifndef GUARD_H_vec
#define GUARD_H_vec

#include <cstddef>//size_t
#include <algorithm>//max�Լ�
#include <memory>//�޸�

using namespace std;
//std::max,uninitialized_fill,uninitialized_copy,allocator
//���� �𷡽� �߻� ������ Ÿ��
template<class T> class Vec {
public:
	//�������̽�
	//Ÿ�� ���ǹ�
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef std::ptrdiff_t difference_type;
	typedef const T& const_reference;
	//������
	Vec() { create(); }
	explicit Vec(size_type n, const T& val = T()) {
		crate(n, val);
	}
	//�ݺ� ������
	Vec(const Vec& v) { create(v.begin, v.end()); }
	Vec& operator = (const Vec&);//���� ex�̷��� �ϰڴ�
	~Vec() { uncreate(); }//�Ҹ���

	//���� ũ��� �ε����� ���� ���ο� �Լ���
	size_type size() const { return avail - data }
	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) const { return data[i]; }
	//�ݺ��ڸ� ��ȯ�ϴ� ���ο� �Լ�
	iterator begin() { return data; }
	const_iterator begin() const { return data; }
	iterator end() { return avail; }
	const_iterator end() const { return avail; }
	//��� �߰� �Լ� (�޸𸮸� ä��� ,Ȯ���Ѵ�)
	void push_back(const T& val) {
		if (avail == limit)//�ʿ��ϴٸ� ���� ���� Ȯ��
			grow();

		unckecked_append(val);//���ο� ��� �߰�


	}
	//�߰��ϴ� �Լ�
	void clear() { uncreate(); }
	bool empty() const{ return data == avail; }
private:
	iterator data; //vec�� ô��° ��Ҹ� ����Ű�� ������
	iterator avail; //���������� ���� ������ ������ ����Ű�� ������
	iterator limit; //����� �� �ִ� ������ ����� ������ ����Ű�� ������


	//������ �ɹ��Լ���(3��)
	allocator<T>alloc; //�޸� �Ҵ��ϴ� ��ü
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);
	void uncreate();
	void grow();
	void unchecked_append(const T&);
};
	template <class T> void Vec<T>::create() {
		data = avail = limit = 0;
	}
	template <class T> void Vec<T>::create(size_type n, const T& val) {
		data = alloc.allocate(n);
		limit = avail = data + n;
		uninitialized_fill(data, limit, val);
	}
	template <class T> void Vec<T>::create(const_iterator i, const_iterator j) {
		data = alloc.allocate(j - i);
		limit = avail = uninitialized_copy(i, j, data);
	}
	//�Ҹ��� �ɹ� �Լ�
	template <class T> void Vec<T>::uncreate() {
		if (data) {
			iterator it = avail; //������ ����� ����Ű�� ������
			while (it != data) //ù��° ��Ҹ� ����Ű�� ������
				alloc.destroy(--it);//
			
			//����� ��� ���� ���� ��ȯ
			alloc.deallocate(data, limit - data);
		}
		//����ִ� vec�� ����Ű���� ������ �缳��
		data = avail = limit = 0;
		//���� ������� ��ȯ
		
	}
	
	//���ο� ��Ҹ��߰��ϱ�
	
	//�޸� ������ �ø��� �Լ�
	template <class T> void Vec<T>::grow() {
		//��������� �ø� ���� ���� ����ϴ� ���� ������ 2�踦 �Ҵ�
		size_type new_size = max(2 * (limit - data), ptrdiff_t(1));
		//���ο� ���� ������ �Ҵ��ϰ� ���� ��ҵ��� ���ο� ���� ������ ����
		iterator new_data = alloc.allocate(new_size);
		
		uncreate();

		//���Ӱ� �Ҵ��� ���� ������ ����Ű�Ű� ������ �缳��
		data = new_data;
		avail = new_avail;
		limit = data + new_size; iterator new_avail = uninitialized_copy(data, avail, new_data);
	}
	
	template <class T> void Vec<T>::unchecked_append(const T& val) {
		alloc.construct(avail++, val);
	}
	//=�ǿ����� ����
	
	template<class T> Vec<T>& Vec<T>::operator =(const Vec& rhs) {
		//�ڱ� �Ҵ� ���� Ȯ��
		if (&rhs != this) {
			//�º��� ���� �迭�� �����ϴ� �޸𸮸� ����
			uncreate();
			//�캯�� ���� ��Ҹ� �º����� ����
			crate(rhs.begin, rhs.end());
		}
		return *this;
	}





#endif