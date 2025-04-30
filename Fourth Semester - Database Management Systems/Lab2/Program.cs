namespace lab2sgbd
{
    /*
    <appSettings>
        <add key="ParentTableName" value="Producator" />
        <add key="ChildTableName" value="Produs" />
        <add key="ParentColumnNames" value="id,numeproducator,tara,website" />
        <add key="ChildColumnNames" value="id,numeprodus,pret,dataexpirare,datafabricare,idproducator" />
        <add key="ParentId" value="id" />
        <add key="ChildId" value="id" />
        <add key="ParentSelectStatement" value="SELECT * FROM Producator" />
        <add key="ChildSelectStatement" value="SELECT * FROM Produs WHERE IdProducator=@id" />
        <add key="InsertStatement" value="INSERT INTO Produs(NumeProdus, Pret, DataExpirare, DataFabricare, IdProducator) VALUES (@numeprodus,@pret,@dataexpirare,@datafabricare,@idproducator)" />
        <add key="UpdateStatement" value="UPDATE Produs SET NumeProdus=@numeprodus, Pret=@pret, DataExpirare=@dataexpirare, DataFabricare=@datafabricare WHERE IdProdus=@id" />
        <add key="DeleteStatement" value="DELETE FROM Produs WHERE IdProdus=@id" />
        <add key="InsertCommandParameters" value="@id,@numeprodus,@pret,@dataexpirare,@datafabricare,@idproducator" />
        <add key="UpdateCommandParameters" value="@id,@numeprodus,@pret,@dataexpirare,@datafabricare" />
    </appSettings>

    <appSettings>
            <add key="ParentTableName" value="Adresa" />
            <add key="ChildTableName" value="Client" />
            <add key="ParentColumnNames" value="id,oras,strada,numarstrada,codpostal" />
            <add key="ChildColumnNames" value="id,numeclient,prenumeclient,idadresa" />
            <add key="ParentId" value="id" />
            <add key="ChildId" value="id" />
            <add key="ParentSelectStatement" value="SELECT * FROM Adresa" />
            <add key="ChildSelectStatement" value="SELECT * FROM Client WHERE IdAdresa=@id" />
            <add key="InsertStatement" value="INSERT INTO Client(NumeClient, PrenumeClient, IdAdresa) VALUES (@numeclient,@prenumeclient,@idadresa)" />
            <add key="UpdateStatement" value="UPDATE Client SET NumeClient=@numeclient, PrenumeClient=@prenumeclient, IdAdresa=@idadresa WHERE IdClient=@id" />
            <add key="DeleteStatement" value="DELETE FROM Client WHERE IdClient=@id" />
            <add key="InsertCommandParameters" value="@id,@numeclient,@prenumeclient,@idadresa" />
            <add key="UpdateCommandParameters" value="@id,@numeclient,@prenumeclient,@idadresa" />
     </appSettings>
     */
    internal static class Program
    {
        /// <summary>
        ///  The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            // To customize application configuration such as set high DPI settings or default font,
            // see https://aka.ms/applicationconfiguration.
            ApplicationConfiguration.Initialize();
            Application.Run(new Form1());
        }
    }
}