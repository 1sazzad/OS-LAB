const User = require("../models/User");
const Patient = require("../models/Patient");
const Doctor = require("../models/Doctor");
const Appointment = require("../models/Appointment");

exports.getUsers = async (req, res) => {
  try {
    const users = await User.find();
    res.json(users);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

exports.getSystemStats = async (req, res) => {
  try {
    const stats = {
      patients: await Patient.countDocuments(),
      doctors: await Doctor.countDocuments(),
      appointments: await Appointment.countDocuments(),
    };
    res.json(stats);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};
