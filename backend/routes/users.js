const express = require("express");
const router = express.Router();
const User = require("../models/User");
const authMiddleware = require("../middleware/authMiddleware");

router.get("/", authMiddleware(["admin"]), async (req, res) => {
  try {
    const users = await User.find();
    res.json(users);
  } catch (err) {
    res.status(500).json({ message: err.message });
  }
});

router.get("/stats", authMiddleware(["admin"]), async (req, res) => {
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
});

module.exports = router;
