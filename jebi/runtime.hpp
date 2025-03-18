#pragma once

namespace jebi
{

class Runtime
{
  public:
    Runtime(const Runtime&) = delete;
    Runtime& operator=(const Runtime&) = delete;
    Runtime(Runtime&&) = delete;
    Runtime& operator=(Runtime&&) = delete;
    
    static Runtime& getInstance();
    
  private:
    Runtime();
};

} // namespace jebi