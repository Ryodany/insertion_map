#pragma once

#include <assert.h>
#include <unordered_map>
#include <iterator>

template <typename K, typename V>
class insertion_map
{
private:
	using Pair = std::pair<K, V>;

	using InternalMap = std::unordered_map<size_t, Pair>;
	using KeyMap = std::unordered_map<K, size_t>;

	size_t m_size;
	size_t m_capacity;
	Pair *m_data;

	InternalMap m_map;
	KeyMap m_keyMap;

public:
	class iterator : public std::iterator<std::bidirectional_iterator_tag, Pair>
	{
	private:
		Pair *m_p;

	public:
		iterator(Pair *x) : m_p(x) { };
		iterator(const iterator& it) : m_p(it.m_p) { };

		iterator& operator++()
		{
			++m_p;
			return *this;
		}

		iterator operator++(int)
		{
			iterator tmp(*this);
			m_p++;
			return tmp;
		}

		bool operator==(const iterator& other) const
		{
			return m_p == other.m_p;
		}

		bool operator!=(const iterator& other) const
		{
			return m_p != other.m_p;
		}

		Pair& operator*() const
		{
			return *m_p;
		}

		Pair* operator->() const
		{
			return m_p;
		}
	};

	insertion_map() : m_size(0), m_capacity(0), m_data(nullptr)
	{
		m_map.clear();
		m_keyMap.clear();
	};

	~insertion_map()
	{
		delete m_data;
	}

	bool insert(const Pair &pair)
	{
		if (m_keyMap.find(pair.first) == m_keyMap.end())
			return insertion(pair.first, pair.second);
		else
			return false;
	}

	bool insert(const K &key, const V &value)
	{
		if (m_keyMap.find(key) == m_keyMap.end())
			return insertion(key, value);
		else
			return false;
	}

	V &operator[](const K &key) const
	{
		if (m_keyMap.find(key) != m_keyMap.end())
			return m_map[m_keyMap[key]].second;
		else
			throw std::runtime_error("Key not found");
	}

	V &operator[](const K &key)
	{
		if (m_keyMap.find(key) != m_keyMap.end())
			return m_map[m_keyMap[key]].second;
		else
		{
			if (insertion(key, V()))
				return (m_data + m_keyMap[key])->second;
			else
				throw std::runtime_error("Unexpected error ocurred while inserting");
		}
			
	}

	iterator begin() { return iterator(m_data); }
	iterator end() { return iterator(m_data + m_size); }

	bool empty() const
	{
		return m_map.empty();
	}

private:
	void manageAllocation(const std::pair<typename InternalMap::iterator, bool> &ret)
	{
		assert(m_size > 0);
		if (m_capacity <= m_size)
		{
			if (m_data)
				delete[]m_data;
			m_capacity = m_size * 2;
			m_data = new Pair[m_capacity];

			assert(m_size == m_map.size());
			size_t count = 0;
			typename std::unordered_map<size_t, Pair>::iterator it;
			for (it = m_map.begin(); count < m_map.size(); it++, count++)
				*(m_data + count) = it->second;
		}
		else
			*(m_data + m_size - 1) = ret.first->second;
	}

	bool insertion(const K &key, const V &value)
	{
		m_keyMap.insert(std::make_pair(key, m_size));
		std::pair<InternalMap::iterator, bool> ret = m_map.insert(std::make_pair(m_size, std::make_pair(key, value)));
		m_size++;

		manageAllocation(ret);

		return ret.second;
	}
};