const Patient = require("../models/Patient");

exports.getPatients = async (req, res) => {
  try {
    const patients = await Patient.find();
    res.json(patients);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};

exports.getPatientProfile = async (req, res) => {
  try {
    const patient = await Patient.findOne({ userId: req.user.id });
    res.json(patient);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
};
