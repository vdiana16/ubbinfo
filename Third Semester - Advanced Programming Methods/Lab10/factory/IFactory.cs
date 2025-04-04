using lab10.model;

namespace lab10.factory;

public interface IFactory
{
    IContainer createContainer(Strategy startegy);
}