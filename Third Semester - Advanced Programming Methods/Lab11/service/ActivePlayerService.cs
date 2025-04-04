using lab11.domain;
using lab11.domain.validator;
using lab11.repository;
using lab11.utils;

namespace lab11.service;

public class ActivePlayerService
{
    private IRepository<int, ActivePlayer> _activePlayerRepository;
    private static readonly IValidator<ActivePlayer> _activePlayerValidator = new ActivePlayerValidator();

    public ActivePlayerService() { }

    public ActivePlayerService(IRepository<int, ActivePlayer> activePlayerRepository)
    {
        _activePlayerRepository = activePlayerRepository;
    }

    public ActivePlayer? Add(ActivePlayer activePlayer)
    {
        _activePlayerValidator.Validate(activePlayer);
        activePlayer.Id = Util.GenerateId(GetAll());
        return _activePlayerRepository.Add(activePlayer);
    }

    public ActivePlayer? Update(ActivePlayer activePlayer)
    {
        _activePlayerValidator.Validate(activePlayer);
        return _activePlayerRepository.Update(activePlayer);
    }

    public ActivePlayer? Delete(int id)
    {
        return _activePlayerRepository.Delete(id);
    }

    public ActivePlayer? Get(int id)
    {
        return _activePlayerRepository.Get(id);
    }

    public IEnumerable<ActivePlayer> GetAll()
    {
        return _activePlayerRepository.GetAll();
    }
}