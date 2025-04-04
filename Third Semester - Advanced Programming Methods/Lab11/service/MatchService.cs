using lab11.domain;
using lab11.domain.dto;
using lab11.domain.validator;
using lab11.exception;
using lab11.repository;
using lab11.utils;

namespace lab11.service;

public class MatchService
{
    private readonly IRepository<int, MatchDto> _matchRepository;
    private static readonly IValidator<Match> _matchValidator = new MatchValidator();
    private GetTeam _getTeam;

    public MatchService(){}
    
    public MatchService(IRepository<int, MatchDto> matchRepository, GetTeam getTeam)
    {
        _matchRepository = matchRepository;
        _getTeam = getTeam;
    }

    private MatchDto MatchToDto(Match match)
    {
        return new MatchDto
        {
            Id = match.Id,
            MatchDate = match.MatchDate,
            IdFirstTeam = match.FirstTeam.Id,
            IdSecondTeam = match.SecondTeam.Id
        };
    }

    private Match DtoToMatch(MatchDto matchDto)
    {
        var firstTeam = _getTeam(matchDto.IdFirstTeam);
        var secondTeam = _getTeam(matchDto.IdSecondTeam);
        if (firstTeam != null && secondTeam != null)
            return new Match
            {
                Id = matchDto.Id,
                MatchDate = matchDto.MatchDate,
                FirstTeam = firstTeam,
                SecondTeam = secondTeam
            };
        throw new ServiceException("Incorrect data");
    }

    public Match? Add(Match match)
    {
        _matchValidator.Validate(match);
        match.Id = Util.GenerateId(GetAll());
        var matchDto = MatchToDto(match);
        return _matchRepository.Add(matchDto) != default ? match : default;
    }

    public Match? Update(Match match)
    { 
        _matchValidator.Validate(match); 
        var matchDto = MatchToDto(match);
        return _matchRepository.Update(matchDto) != default ? match : default;
    }
    
    public Match? Delete(int id)
    {
        var result = _matchRepository.Delete(id);
        return result != default ? DtoToMatch(result) : default;
    }

    public Match? Get(int id)
    {
        return GetAll().FirstOrDefault(x => x.Id == id);
    }

    public IEnumerable<Match> GetAll()
    {
        return _matchRepository.GetAll().Select<MatchDto, Match>(DtoToMatch);
    }

    public IEnumerable<Match> GetAllMatchesFromAPeriod(DateTime startDate, DateTime endDate)
    {
        return GetAll().Where(x => x.MatchDate >= startDate && x.MatchDate <= endDate);
    }
}