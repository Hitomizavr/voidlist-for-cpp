// void_list.cpp
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Следующие 4 функции ничего не знают о содержимом списка.

/// Возвращает ссылку на указатель на следующее звено звена link.
void*& next(void *link)
{
  return *(void**)link;
}

/// Вставляет link перед head и возвращает link (теперь это -- новая голова списка).
void* insert_head(void *head, void *link)
{
  next(link) = head;
  return link;
}

/// Вычисляет длину списка.
size_t size(void *head)
{
  size_t sz = 0;
  for (; head; head = next(head))
    ++sz;
  return sz;
}

/// Указатель на функцию, выполняющую удаление звена.
using Link_delete = void(*)(void*);

/// Удаляет список, используя пользовательскую функцию удаления.
void delete_list(void *head, Link_delete link_delete)
{
  while (head)
  {
    auto next_head = next(head);
    link_delete(head);
    head = next_head;
  }    
}


///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>

/// Звено списка -- одна строка.
struct Line
{
  void *prev;
  string line;
};

/// Вывести строку и удалить объект Line.
void print_and_delete(void *ptr)
{
  auto line = (Line*)ptr;
  cout << line->line << '\n';
  delete line;
}

int main()
{
  Line *head = nullptr;

  // Чтение строк.
  for (string line; getline(cin, line);)
  {
    Line *new_line = new Line;
    new_line->line = line;
    head = (Line*)insert_head(head, new_line);
  }

  // Вывод количества строк -- элементов списка.
  cout << "\nLines: " << size(head) << "\n\n";

  // Вывод строк в обратном порядке.
  delete_list(head, print_and_delete);

  cin.clear();
  cin.ignore();

  return EXIT_SUCCESS;
}
