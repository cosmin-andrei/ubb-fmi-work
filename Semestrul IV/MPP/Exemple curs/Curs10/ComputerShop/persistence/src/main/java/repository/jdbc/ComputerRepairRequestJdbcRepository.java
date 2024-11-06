package repository.jdbc;

import model.ComputerRepairRequest;
import model.RequestStatus;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;
import repository.ComputerRepairRequestRepository;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Properties;

@Component
public class ComputerRepairRequestJdbcRepository implements ComputerRepairRequestRepository {

    private JdbcUtils jdbcUtils;

    private final static Logger logger= LogManager.getLogger(ComputerRepairRequestJdbcRepository.class);

    @Autowired
    public ComputerRepairRequestJdbcRepository(Properties props) {
        jdbcUtils=new JdbcUtils(props);

    }

    @Override
    public List<ComputerRepairRequest> findByOwnerName(String name) {
        return null;
    }

    @Override
    public List<ComputerRepairRequest> findByModel(String modelN) {

        logger.traceEntry();
        Connection con=jdbcUtils.getConnection();
        List<ComputerRepairRequest> requests=new ArrayList<>();
        try(PreparedStatement preStmt=con.prepareStatement("select * from RepairRequests where model like ?")) {
            preStmt.setString(1,"%"+modelN+"%");
            try(ResultSet result=preStmt.executeQuery()) {
                while (result.next()) {
                    int id = result.getInt("id");
                    String ownerName = result.getString("ownerName");
                    String ownerAddress = result.getString("ownerAddress");
                    String phoneNumber = result.getString("phoneNumber");
                    String model = result.getString("model");
                    String date = result.getString("date");
                    String problem = result.getString("problem");
                    String status = result.getString("status");

                    ComputerRepairRequest request=new ComputerRepairRequest(ownerName, ownerAddress, phoneNumber,model,date,problem);
                    request.setID(id);
                    request.setStatus(Enum.valueOf(RequestStatus.class,status));

                    requests.add(request);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            System.err.println("Error DB "+e);
        }
        return logger.traceExit(requests);
    }

    @Override
    public List<ComputerRepairRequest> filterByStatus(RequestStatus statusN) {
        logger.traceEntry();
        Connection con=jdbcUtils.getConnection();
        List<ComputerRepairRequest> requests=new ArrayList<>();
        try(PreparedStatement preStmt=con.prepareStatement("select * from RepairRequests where status =?")) {

            preStmt.setString(1,statusN.name());
            try(ResultSet result=preStmt.executeQuery()) {
                while (result.next()) {
                    int id = result.getInt("id");
                    String ownerName = result.getString("ownerName");
                    String ownerAddress = result.getString("ownerAddress");
                    String phoneNumber = result.getString("phoneNumber");
                    String model = result.getString("model");
                    String date = result.getString("date");
                    String problem = result.getString("problem");
                    String status = result.getString("status");

                    ComputerRepairRequest request=new ComputerRepairRequest(ownerName, ownerAddress, phoneNumber,model,date,problem);
                    request.setID(id);
                    request.setStatus(Enum.valueOf(RequestStatus.class,status));

                    requests.add(request);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            System.err.println("Error DB "+e);
        }
        return logger.traceExit(requests);
    }


    @Override
    public List<ComputerRepairRequest> filterByModelAndStatus(String modelN, RequestStatus statusN) {
        logger.traceEntry();
        Connection con=jdbcUtils.getConnection();
        List<ComputerRepairRequest> requests=new ArrayList<>();
        try(PreparedStatement preStmt=con.prepareStatement("select * from RepairRequests where model like ? and status =?")) {
            preStmt.setString(1,"%"+modelN+"%");
            preStmt.setString(2,statusN.name());
            try(ResultSet result=preStmt.executeQuery()) {
                while (result.next()) {
                    int id = result.getInt("id");
                    String ownerName = result.getString("ownerName");
                    String ownerAddress = result.getString("ownerAddress");
                    String phoneNumber = result.getString("phoneNumber");
                    String model = result.getString("model");
                    String date = result.getString("date");
                    String problem = result.getString("problem");
                    String status = result.getString("status");

                    ComputerRepairRequest request=new ComputerRepairRequest(ownerName, ownerAddress, phoneNumber,model,date,problem);
                    request.setID(id);
                    request.setStatus(Enum.valueOf(RequestStatus.class,status));

                    requests.add(request);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            System.err.println("Error DB "+e);
        }
        return logger.traceExit(requests);
    }

    @Override
    public ComputerRepairRequest add(ComputerRepairRequest elem) {

        logger.traceEntry("saving request {} ",elem);
        Connection con=jdbcUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement("insert into RepairRequests (ownerName, ownerAddress, phoneNumber, model,date, problem,status) values (?,?,?,?,?,?,?)", Statement.RETURN_GENERATED_KEYS)){

            preStmt.setString(1,elem.getOwnerName());
            preStmt.setString(2,elem.getOwnerAddress());
            preStmt.setString(3,elem.getPhoneNumber());
            preStmt.setString(4,elem.getModel());
            preStmt.setString(5,elem.getDate());
            preStmt.setString(6,elem.getProblemDescription());
            preStmt.setString(7,elem.getStatus().name());
            int result=preStmt.executeUpdate();
            logger.trace("Saved {} instances",result);
            if (result>0){
                //obtinem ID-ul generat de baza de date
                ResultSet rs = preStmt.getGeneratedKeys();
                if (rs.next()) {
                    int id=rs.getInt(1);
                    elem.setID(id);
                    logger.trace("Generated id {} ",id);
                }

            }
        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB "+ex);
        }
        return logger.traceExit(elem);
    }

    @Override
    public void delete(ComputerRepairRequest elem) {
        //To do
    }

    @Override
    public void update(ComputerRepairRequest elem, Integer id) {
        logger.traceEntry("updating request {} ",elem);
        Connection con=jdbcUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement("update RepairRequests set status=? where id=?")){

            preStmt.setString(1,elem.getStatus().name());
            preStmt.setInt(2,elem.getID());
            int result=preStmt.executeUpdate();
            logger.trace("Updated {} instances",result);

        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB "+ex);
        }
         logger.traceExit();

    }

    @Override
    public ComputerRepairRequest findById(Integer idS) {

        logger.traceEntry("find by id request {} ",idS);
        Connection con=jdbcUtils.getConnection();
        try(PreparedStatement preStmt=con.prepareStatement("select * from RepairRequests  where id=?")){

            preStmt.setInt(1,idS);

            try(ResultSet result=preStmt.executeQuery()) {
                if (result.next()) {
                    int id = result.getInt("id");
                    String ownerName = result.getString("ownerName");
                    String ownerAddress = result.getString("ownerAddress");
                    String phoneNumber = result.getString("phoneNumber");
                    String model = result.getString("model");
                    String date = result.getString("date");
                    String problem = result.getString("problem");
                    String status = result.getString("status");

                    ComputerRepairRequest request=new ComputerRepairRequest(ownerName, ownerAddress, phoneNumber,model,date,problem);
                    request.setID(id);
                    request.setStatus(Enum.valueOf(RequestStatus.class,status));

                    return  logger.traceExit(request);
                }
            }

        }catch (SQLException ex){
            logger.error(ex);
            System.err.println("Error DB "+ex);
        }
        logger.traceExit();
        return null;
    }

    @Override
    public Iterable<ComputerRepairRequest> findAll() {
        return null;
    }

    @Override
    public Collection<ComputerRepairRequest> getAll() {
        logger.traceEntry();
        Connection con=jdbcUtils.getConnection();
        List<ComputerRepairRequest> requests=new ArrayList<>();
        try(PreparedStatement preStmt=con.prepareStatement("select * from RepairRequests ")) {
            try(ResultSet result=preStmt.executeQuery()) {
                while (result.next()) {
                    int id = result.getInt("id");
                    String ownerName = result.getString("ownerName");
                    String ownerAddress = result.getString("ownerAddress");
                    String phoneNumber = result.getString("phoneNumber");
                    String model = result.getString("model");
                    String date = result.getString("date");
                    String problem = result.getString("problem");
                    String status = result.getString("status");

                    ComputerRepairRequest request=new ComputerRepairRequest(ownerName, ownerAddress, phoneNumber,model,date,problem);
                    request.setID(id);
                    request.setStatus(Enum.valueOf(RequestStatus.class,status));

                    requests.add(request);
                }
            }
        } catch (SQLException e) {
            logger.error(e);
            System.err.println("Error DB "+e);
        }
        return logger.traceExit(requests);
    }
}
