    // See https://aka.ms/new-console-template for more information

using lab11.domain;
using lab11.domain.dto;
using lab11.repository;
using lab11.repository.file;
using lab11.service;
using Console = lab11.ui.Console;

public class Program
{
    public static void Main(string[] args)
    {
        IRepository<int,Team> teamRepository = new TeamFileRepo("Teams");
        IRepository<int,Student> studentRepository = new StudentFileRepo("Students");
        IRepository<int,PlayerDto> playerRepository = new PlayerFileRepo("Players");
        IRepository<int,MatchDto> matchRepository = new MatchFileRepo("Matches");
        IRepository<int,ActivePlayer> activePlayerRepository = new ActivePlayerFileRepo("ActivePlayers");

        var teamService = new TeamService(teamRepository);
        var studentService = new StudentService(studentRepository);
        var playerService = new PlayerService(playerRepository, studentService.Get, teamService.Get);
        var matchService = new MatchService(matchRepository, teamService.Get);
        var activePlayerService = new ActivePlayerService(activePlayerRepository);
        var service = new Service(teamService, studentService, playerService, matchService, activePlayerService);

        var console = new Console(service);

        console.Start();
    }
}
    
