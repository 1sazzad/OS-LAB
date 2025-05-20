const Doctor = require("../models/Doctor");

exports.getDoctors = async (req, res) => {
  try {
    const doctors = await Doctor.find();
    res.json(doctors);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

exports.getDoctorSchedule = async (req, res) => {
  try {
    const doctor = await Doctor.findOne({ userId: req.user.id });
    const appointments = await Appointment.find({ doctorId: doctor._id });
    res.json(appointments);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};
