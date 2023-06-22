#pragma once

#include "value.h"
#include "value_map.h"

#include <trieste/driver.h>

namespace rego
{
  class Variable
  {
  public:
    Variable(const Node& local);
    bool depends_on(const Location& var) const;
    void remove(const Value& value);
    bool intersect_with(const Values& others);
    bool initialize(const Values& others);
    std::string str() const;
    bool remove_invalid_values();
    bool all_falsy() const;
    void mark_invalid_values();
    void mark_valid_values();
    Values valid_values() const;
    std::size_t increase_dependency_score(std::size_t amount);
    Node to_term() const;
    const Node& local() const;
    const std::set<Location>& dependencies() const;
    Node bind();

    std::size_t dependency_score() const;
    bool is_unify() const;
    bool is_user_var() const;
    bool initialized() const;
    Location name() const;

    static void compute_dependency_scores(
      std::map<Location, Variable>& variables);

    static std::size_t detect_cycles(std::map<Location, Variable>& variables);

    template <typename T>
    void insert_dependencies(T start, T end)
    {
      m_dependencies.insert(start, end);
    }

    friend std::ostream& operator<<(std::ostream& os, const Variable& variable);
    friend std::ostream& operator<<(
      std::ostream& os, const std::map<Location, Variable>& variables);

  private:
    std::size_t compute_dependency_score(
      std::map<Location, Variable>& variables);

    bool has_cycle(const std::map<Location, Variable>& variables) const;

    Node m_local;
    std::set<Location> m_dependencies;
    ValueMap m_values;
    bool m_unify;
    bool m_user_var;
    bool m_visited;
    bool m_initialized;
    std::size_t m_dependency_score;
  };
}